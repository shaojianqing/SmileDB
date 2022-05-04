#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/type.h"
#include "../data/objectType.h"
#include "../data/stringType.h"
#include "../data/hashMap.h"
#include "../data/arrayList.h"
#include "../page/byteBuffer.h"
#include "../page/header.h"
#include "../table/table.h"
#include "../page/record.h"
#include "../page/page.h"

#include "storage.h"

static int keyCompare(List *primaryKeyValues, List* targetKeyValues, List* primaryKeyColumns);

static DataRecord* searchBinaryByDirectory(List *targetKeyValues, Table *table, IndexPage *indexPage, File *ibdFile);

static DataRecord* searchLinearInPage(List *targetKeyValues, Table *table, IndexPage *indexPage, u32 recordPosition, File *ibdFile);

DataRecord* queryDataRecordByPrimaryKey(List *targetKeyValues, Table *table, File *ibdFile) {

    IndexPage *rootIndexPage = (IndexPage *)loadPage(ibdFile, ROOT_PAGE_NUMBER, table);
    return searchBinaryByDirectory(targetKeyValues, table, rootIndexPage, ibdFile); 
}

static DataRecord* searchBinaryByDirectory(List *targetKeyValues, Table *table, IndexPage *indexPage, File *ibdFile) {

    u16 *directorySlotList = indexPage->directorySlotList;
    u16 directorySlotCount = indexPage->directorySlotCount;

    Page* super = (Page *)indexPage;
    ByteBuffer *byteBuffer = super->pageBuffer;
    u32 start = 0, end = directorySlotCount-1, mid = 0;
    DataRecord *dataRecord = NULL;
    while(start<=end) {
        mid = (start + end)/2;
        u32 recordPosition = directorySlotList[mid];
        byteBuffer->setPosition(byteBuffer, recordPosition);
        dataRecord = readDataRecord(byteBuffer, table);

        List* primaryValues = dataRecord->getPrimaryKeyValues(dataRecord);
        int compareResult = keyCompare(primaryValues, targetKeyValues, table->keyColumnList);
        if (compareResult==0) {
            return searchLinearInPage(targetKeyValues, table, indexPage, recordPosition, ibdFile);
        } else if (compareResult>0) {
            end = mid - 1;
        } else if (compareResult<0) {
            start = mid + 1;
        }
    }

    u32 recordPosition = directorySlotList[start - 1];
    return searchLinearInPage(targetKeyValues, table, indexPage, recordPosition, ibdFile);
}

static DataRecord* searchLinearInPage(List *targetKeyValues, Table *table, IndexPage *indexPage, u32 recordPosition, File *ibdFile) {
    Page* super = (Page *)indexPage;
    ByteBuffer *byteBuffer = super->pageBuffer;
    byteBuffer->setPosition(byteBuffer, recordPosition);
    DataRecord *dataRecord = readDataRecord(byteBuffer, table);
    DataRecord *prevDataRecord = dataRecord;
    DataRecord *supremum = indexPage->supremum;

    RecordHeader *recordHeader = dataRecord->header;
    while(recordHeader->recordType!=RECORD_TYPE_SUPREMUN) {
        List* primaryKeyValues = dataRecord->getPrimaryKeyValues(dataRecord);
        int compareResult = keyCompare(primaryKeyValues, targetKeyValues, table->keyColumnList);
        if (compareResult>0) {
            if (indexPage->isLeafPage(indexPage)) {
                return NULL;
            } else {
                u64 childPageNumber = prevDataRecord->childPageNumber;
                if (prevDataRecord->header->recordType==RECORD_TYPE_INFIMUM) {
                    childPageNumber = dataRecord->childPageNumber;
                }
                indexPage = (IndexPage *)loadPage(ibdFile, childPageNumber, table);
                return searchBinaryByDirectory(targetKeyValues, table, indexPage, ibdFile);
            }
        } else if (compareResult==0) {
            if (indexPage->isLeafPage(indexPage)) {
                return dataRecord;
            } else {
                u64 childPageNumber = dataRecord->childPageNumber;
                return searchBinaryByDirectory(targetKeyValues, table, indexPage, ibdFile);
            }
        }
            
        byteBuffer->setPosition(byteBuffer, dataRecord->getNextRecordPosition(dataRecord));
        DataRecord *nextRecord = readDataRecord(byteBuffer, table);
        prevDataRecord = dataRecord;
        dataRecord = nextRecord;
        recordHeader = dataRecord->header;
    }

    if (indexPage->isLeafPage(indexPage)) {
        return NULL;
    } else {
        u64 childPageNumber = prevDataRecord->childPageNumber;
        return searchBinaryByDirectory(targetKeyValues, table, indexPage, ibdFile);
    }
}

static int keyCompare(List *recordKeyValues, List* targetKeyValues, List* recordKeyColumns) {
    u32 recordKeyValueCount = recordKeyValues->getSize(recordKeyValues);
    u32 targetKeyValueCount = targetKeyValues->getSize(targetKeyValues);
    u32 recordKeyColumnCount = recordKeyColumns->getSize(recordKeyColumns);

    if (recordKeyValueCount!=targetKeyValueCount || recordKeyValueCount!=recordKeyColumnCount) {
        printf("recordKeyValueCount and targetKeyValueCount and recordKeyColumnCount not Equal!\n\n");
        printf("recordKeyValueCount:%u\n", recordKeyValueCount);
        printf("targetKeyValueCount:%u\n", targetKeyValueCount);
        printf("recordKeyColumnCount:%u\n", recordKeyColumnCount);

        String *targetKeyValue = targetKeyValues->get(targetKeyValues, 0);

        printf("targetKeyValue:%s\n", targetKeyValue->value);

        exit(1);
    }

    u32 i=0;
    for(i=0;i<recordKeyValueCount;++i) {
        String *recordKeyValue = recordKeyValues->get(recordKeyValues, i);
        String *targetKeyValue = targetKeyValues->get(targetKeyValues, i);

        if (strcmp(recordKeyValue->value, MAXIMUM_VALUE)==0) {
            return 1;
        }

        if (strcmp(recordKeyValue->value, MINIMUM_VALUE)==0) {
            return -1;
        }

        if (strcmp(targetKeyValue->value, MAXIMUM_VALUE)==0) {
            return -1;
        }

        if (strcmp(targetKeyValue->value, MINIMUM_VALUE)==0) {
            return 1;
        }

        int compareResult = strcmp(recordKeyValue->value, targetKeyValue->value);
        if (compareResult!=0) {
            return compareResult;
        }
    }
    return 0;
}