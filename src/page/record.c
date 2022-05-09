#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/type.h"
#include "../data/objectType.h"
#include "../data/stringType.h"
#include "../data/arrayList.h"
#include "../data/hashMap.h"
#include "../table/table.h"

#include "byteBuffer.h"
#include "header.h"
#include "columnParse.h"
#include "record.h"

#define VARLENINFO "VarLenInfo"

static void makeInfimumRecord(DataRecord *dataRecord);

static void makeSupremumRecord(DataRecord *dataRecord);

static List* getPrimaryKeyValues(DataRecord *this);

static int getNextRecordPosition(DataRecord *this);

static bool varLenInfoEquals(Object *obj1, Object *obj2);

static Type* getObject(DataRecord *this, String *cloumnName);

static void putObject(DataRecord *this, String *cloumnName, Type *value);

static u32 makeNullByteSize(List *nullableColumns);

static byte* makeNullBitmap(ByteBuffer *byteBuffer, List *nullableColumns);

static List* makeNullColumn(byte *nullableColumnBitmap, List *nullableColumns);

VarLenInfo* createVarLenInfo(String *columnName, u16 columnLength, bool isOverflowPage);

static List* makeVariableLengthList(ByteBuffer *byteBuffer, u32 nullableColumnByteSize, List* variableLenColumnList, List* nullColumnList);

static void putColumnValue(DataRecord *record, ByteBuffer *byteBuffer, Column *column, u32 variableLengthIndex, List *variableLenColumnList);

DataRecord* readDataRecord(ByteBuffer *byteBuffer, Table *table) {

    u32 primaryKeyPosition = byteBuffer->getPosition(byteBuffer);
    byteBuffer->decreasePosition(byteBuffer, RECORD_BUFFER_SIZE);
    RecordHeader *recordHeader = (RecordHeader *)malloc(sizeof(RecordHeader));
    initRecordHeader(byteBuffer, recordHeader);
    DataRecord *dataRecord = constructDataRecord(recordHeader, table);

    // Set the primaryKey as before
    byteBuffer->setPosition(byteBuffer, primaryKeyPosition);
    // For INFIMUM or SUPREMUN Type, Directly set the primaryKeyPosition
    if (recordHeader->recordType == RECORD_TYPE_INFIMUM || 
            recordHeader->recordType == RECORD_TYPE_SUPREMUN) {
        dataRecord->primaryKeyPosition = byteBuffer->getPosition(byteBuffer);
        if (recordHeader->recordType == RECORD_TYPE_INFIMUM) {
            makeInfimumRecord(dataRecord);
        } else if (recordHeader->recordType == RECORD_TYPE_SUPREMUN) {
            makeSupremumRecord(dataRecord);
        }
    }
    // For Other Record Type, Read the Record Data 
    else {
        // Process the nullable column list
        byteBuffer->decreasePosition(byteBuffer, RECORD_BUFFER_SIZE);
        byte* nullColumnBitmap = makeNullBitmap(byteBuffer, table->nullableColumnList);
        List* nullColumnList = makeNullColumn(nullColumnBitmap, table->nullableColumnList);
        u32 nullableColumnByteSize = makeNullByteSize(table->nullableColumnList);

        List *variableLenColumnList = NULL;
        if (recordHeader->recordType==RECORD_NODE_POINTER) {
            variableLenColumnList = table->keyVarLenColumnList;
        } else if (recordHeader->recordType==RECORD_CONVENTIONAL) {
            variableLenColumnList = table->variableLenColumnList;
        }
        List *variableLengthList = makeVariableLengthList(byteBuffer, nullableColumnByteSize, variableLenColumnList, nullColumnList);
        byteBuffer->setPosition(byteBuffer, primaryKeyPosition);
        List* primaryKeyColumnList = table->keyColumnList;
        u32 primaryKeyColumnCount = primaryKeyColumnList->getSize(primaryKeyColumnList);
        u32 variableLengthIndex = 0;
        if (primaryKeyColumnCount>0) {
            u32 i=0;
            for (i=0;i<primaryKeyColumnCount;++i) {
                Column *primaryKey = primaryKeyColumnList->get(primaryKeyColumnList, i);
                if (nullColumnList->containsObject(nullColumnList, primaryKey->name)) {
                    dataRecord->putObject(dataRecord, primaryKey->name, NULL);
                } else {
                    putColumnValue(dataRecord, byteBuffer, primaryKey, variableLengthIndex, variableLengthList);
                    if (primaryKey->isVariableLength(primaryKey)) {
                        variableLengthIndex++;
                    }
                }
            }
        } else {
            byteBuffer->increasePosition(byteBuffer, ROW_ID_SIZE);
        }

        dataRecord->primaryKeyPosition = primaryKeyPosition;
        if (recordHeader->recordType==RECORD_NODE_POINTER) {
            u32 childPageNumber = byteBuffer->readUnsignedInteger(byteBuffer);
            dataRecord->childPageNumber = childPageNumber;
        } else if (recordHeader->recordType==RECORD_CONVENTIONAL) {
            byteBuffer->increasePosition(byteBuffer, TRANSACTION_ID_SIZE + ROLL_POINT_SIZE);
            List *columnList = table->columnList;
            u32 columnCount = columnList->getSize(columnList);
            u32 i=0;
            for (i=0;i<columnCount;++i) {
                Column *column = columnList->get(columnList, i);
                if (primaryKeyColumnList->containsObject(primaryKeyColumnList, column) == FALSE) {
                    if (nullColumnList->containsObject(nullColumnList, column->name)) {
                        dataRecord->putObject(dataRecord, column->name, NULL);
                    } else {
                        putColumnValue(dataRecord, byteBuffer, column, variableLengthIndex, variableLengthList);
                        if (column->isVariableLength(column)) {
                            variableLengthIndex++;
                        }
                    }
               }
           }
        }
    }
    byteBuffer->setPosition(byteBuffer, dataRecord->getNextRecordPosition(dataRecord));
    return dataRecord;
}

DataRecord* constructDataRecord(RecordHeader *header, Table *table) {
    DataRecord *dataRecord = (DataRecord *)malloc(sizeof(DataRecord));
    dataRecord->recordData = createHashMap(8);
    dataRecord->getNextRecordPosition = getNextRecordPosition;
    dataRecord->getPrimaryKeyValues = getPrimaryKeyValues;
    dataRecord->getObject = getObject;
    dataRecord->putObject = putObject;
    dataRecord->header = header;
    dataRecord->table = table;

    return dataRecord;
}

static List* getPrimaryKeyValues(DataRecord *this) {
    Table *table = this->table;
    HashMap *recordData = this->recordData;

    List *primaryValues = createArrayList(2);
    List *primaryKeys = table->keyColumnList;
    u32 primaryKeyCount = primaryKeys->getSize(primaryKeys);
    u32 i=0;
    for (i=0;i<primaryKeyCount;++i) {
        Column *primaryKey = primaryKeys->get(primaryKeys, i);
        if (recordData->containsKey(recordData, primaryKey->name)) {
            Type *primaryValue = recordData->get(recordData, primaryKey->name);
            primaryValues->add(primaryValues, primaryValue);
        }
    }
    return primaryValues;
}

static int getNextRecordPosition(DataRecord *this) {
    RecordHeader *recordHeader = this->header;
    return this->primaryKeyPosition + recordHeader->nextRecordOffset;
}

static Type* getObject(DataRecord *this, String *cloumnName) {
    HashMap *recordData = this->recordData;
    if (recordData->containsKey(recordData, cloumnName)) {
        return recordData->get(recordData, cloumnName);
    }
    return NULL;
}

static void putObject(DataRecord *this, String *cloumnName, Type *columnValue) {
    HashMap *recordData = this->recordData;
    recordData->put(recordData, cloumnName, columnValue);
}

static void makeInfimumRecord(DataRecord *dataRecord) {
    Table *table = dataRecord->table;
    List *columnNames = table->columnNames;
    u32 columnNameCount = columnNames->getSize(columnNames);
    u32 i=0;
    for (i=0;i<columnNameCount;++i) {
        String *columnName = columnNames->get(columnNames, i);
        String *minimumValue = createString(MINIMUM_VALUE);
        dataRecord->putObject(dataRecord, columnName, minimumValue);
    }
}

static void makeSupremumRecord(DataRecord *dataRecord) {
    Table *table = dataRecord->table;
    List *columnNames = table->columnNames;
    u32 columnNameCount = columnNames->getSize(columnNames);
    u32 i=0;
    for (i=0;i<columnNameCount;++i) {
        String *columnName = columnNames->get(columnNames, i);
        String *maximumValue = createString(MAXIMUM_VALUE);
        dataRecord->putObject(dataRecord, columnName, maximumValue);
    }
}

static u32 makeNullByteSize(List *nullableColumns) {
    u32 nullableColumnCount = nullableColumns->getSize(nullableColumns);
    u32 byteSize = nullableColumnCount/BIT_COUNT_PER_BYTE; 
    if (nullableColumnCount%BIT_COUNT_PER_BYTE!=0) {
        byteSize++;
    }
    return byteSize;
}

static byte* makeNullBitmap(ByteBuffer *byteBuffer, List *nullableColumns) {
    u32 nullableColumnCount = nullableColumns->getSize(nullableColumns);
    u32 byteSize = makeNullByteSize(nullableColumns);
    byteBuffer->decreasePosition(byteBuffer, byteSize);

    byte* nullableBitMap = (byte*)malloc(nullableColumnCount);
    memset(nullableBitMap, 0, nullableColumnCount);
    byte* byteArray = byteBuffer->readByteArray(byteBuffer, byteSize);

    u32 i=0;
    for (i=0;i<nullableColumnCount;++i) {
        u32 index = byteSize - 1 - i/BIT_COUNT_PER_BYTE;
        nullableBitMap[i] = ((byteArray[index] >> (i%BIT_COUNT_PER_BYTE))&1);
    }
    return nullableBitMap;
}

static List* makeNullColumn(byte *nullableColumnBitmap, List *nullColumns) {
    u32 nullColumnCount = nullColumns->getSize(nullColumns);
    List* nullColumnList = createArrayList(8);
    u32 i=0;
    for (i=0;i<nullColumnCount;++i) {
        if (nullableColumnBitmap[i]==1) {
            Column *nullColumn = nullColumns->get(nullColumns, i);
            nullColumnList->add(nullColumnList, nullColumn->name);
        }
    }
    return nullColumnList;
}

static List* makeVariableLengthList(ByteBuffer *byteBuffer, u32 nullableColumnByteSize, List* variableLenColumnList, List* nullColumnList) {
    u32  variableLenColumnCount =  variableLenColumnList->getSize(variableLenColumnList);
    byteBuffer->decreasePosition(byteBuffer, nullableColumnByteSize);

    List *variableLengthList = createArrayList(8);
    u32 i=0;
    for (i=0;i<variableLenColumnCount;++i) {
        Column *column = variableLenColumnList->get(variableLenColumnList, i);
        if (nullColumnList->containsObject(nullColumnList, column->name) == FALSE) {
            byteBuffer->decreasePosition(byteBuffer, sizeof(byte));
            u16 columnLength = byteBuffer->readByte(byteBuffer);
            byteBuffer->decreasePosition(byteBuffer, sizeof(byte));

            VarLenInfo *varLenInfo = createVarLenInfo(column->name, columnLength, FALSE);
            variableLengthList->add(variableLengthList, varLenInfo);
        }
    }
    return variableLengthList;
}

static void putColumnValue(DataRecord *record, ByteBuffer *byteBuffer, Column *column, u32 variableLengthIndex, List *variableLenColumnList) {
    ColumnParser *columnParser = constructColumnParser(column->type);
    if (columnParser!=NULL) {
        if (column->isVariableLength(column)) {
            VarLenInfo *varLenInfo = (VarLenInfo *)variableLenColumnList->get(variableLenColumnList, variableLengthIndex);
            Type *columnValue = columnParser->readObjectWithLength(byteBuffer, varLenInfo->columnLength);
            record->putObject(record, column->name, columnValue);
        } else if (column->isFixedLength(column)) {
            Type *columnValue = columnParser->readObjectWithLength(byteBuffer, column->length);
            record->putObject(record, column->name, columnValue);
        } else {
            Type *columnValue = columnParser->readObjectWithColumn(byteBuffer, column);
            record->putObject(record, column->name, columnValue);
        }
    } else {
        printf("ColumnType:%s,no columnParser!\n", column->type->value);
    }
}

VarLenInfo* createVarLenInfo(String *columnName, u16 columnLength, bool isOverflowPage) {

    VarLenInfo *varLenInfo = (VarLenInfo *)malloc(sizeof(VarLenInfo));

    Object *super = (Object*)varLenInfo;
    super->name = VARLENINFO;
    super->equals = varLenInfoEquals;
    super->compare = NULL;
    super->hashCode = NULL;
    super->comparable = FALSE;

    varLenInfo->columnName = columnName;
    varLenInfo->columnLength = columnLength;
    varLenInfo->isOverflowPage = isOverflowPage;

    return varLenInfo;
}

static bool varLenInfoEquals(Object *obj1, Object *obj2) {
	if (obj1!=NULL && obj2!=NULL) {
		if (obj1==obj2) {
			return TRUE;		
		} else {
			VarLenInfo *varLenInfo1 = (VarLenInfo *)obj1;
			VarLenInfo *varLenInfo2 = (VarLenInfo *)obj2;
			if (varLenInfo1->columnName!=NULL && varLenInfo2->columnName!=NULL) {
				return (strcmp(varLenInfo1->columnName->value, varLenInfo2->columnName->value)==0);
			} else if (varLenInfo1->columnName==NULL && varLenInfo2->columnName==NULL) {
				return TRUE;
			}
			return FALSE;
		}
	} else if (obj1==NULL && obj2==NULL) {
		return TRUE;
	} else {
		return FALSE;	
	}
}