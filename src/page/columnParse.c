#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/type.h"
#include "../data/objectType.h"
#include "../data/stringType.h"
#include "../data/byteType.h"
#include "../data/shortType.h"
#include "../data/integerType.h"
#include "../data/longType.h"
#include "../data/floatType.h"
#include "../data/doubleType.h"
#include "../data/datetimeType.h"
#include "../data/arrayList.h"
#include "../data/hashMap.h"
#include "../table/table.h"

#include "byteBuffer.h"
#include "columnParse.h"

#define DATETIME_MAIN_SIZE      5
#define SIZE_OF_BYTE            1
#define SIZE_OF_SHORT           2
#define SIZE_OF_INT             4
#define SIZE_OF_LONG            8

static bool hasInitialized = FALSE;

static ColumnParser varcharColumnParser;

static ColumnParser integerColumnParser;

static ColumnParser tinyintColumnParser;

static ColumnParser smallintColumnParser;

static ColumnParser bigintColumnParser;

static ColumnParser floatColumnParser;

static ColumnParser doubleColumnParser;

static ColumnParser datetimeColumnParser;

static void initializeColumnParser();

static Type *readObjectForVarchar(ByteBuffer *byteBuffer, u32 length);

static Type *readObjectForFixchar(ByteBuffer *byteBuffer, Column *column);

static Type* readObjectForTinyInteger(ByteBuffer *byteBuffer, Column *column);

static Type* readObjectForSmallInteger(ByteBuffer *byteBuffer, Column *column);

static Type* readObjectForInteger(ByteBuffer *byteBuffer, Column *column);

static Type* readObjectForBigInteger(ByteBuffer *byteBuffer, Column *column);

static Type* readObjectForFloat(ByteBuffer *byteBuffer, Column *column);

static Type* readObjectForDouble(ByteBuffer *byteBuffer, Column *column);

static Type* readObjectForDatetime(ByteBuffer *byteBuffer, Column *column);

ColumnParser* constructColumnParser(String *columnType) {
    initializeColumnParser();
    if (strcmp(columnType->value, TYPE_VARCHAR)==0) {
        return &varcharColumnParser;
    } else if (strcmp(columnType->value, TYPE_DATETIME)==0) {
        return &datetimeColumnParser;
    } else if (strcmp(columnType->value, TYPE_TINYINT)==0) {
        return &tinyintColumnParser;
    } else if (strcmp(columnType->value, TYPE_SMALLINT)==0) {
        return &smallintColumnParser;
    } else if (strcmp(columnType->value, TYPE_INT)==0) {
        return &integerColumnParser;
    } else if (strcmp(columnType->value, TYPE_BIGINT)==0) {
        return &bigintColumnParser;
    } else if (strcmp(columnType->value, TYPE_SMALLINT)==0) {
        return &tinyintColumnParser;
    } else if (strcmp(columnType->value, TYPE_FLOAT)==0) {
        return &floatColumnParser;
    } else if (strcmp(columnType->value, TYPE_DOUBLE)==0) {
        return &doubleColumnParser;
    } else {
        printf("Column Type Not Supported!columnType:%s\n", columnType->value);
        exit(-1);
    }
    
    return NULL;
}

static void initializeColumnParser() {
    if (hasInitialized==FALSE) {
        varcharColumnParser.readObjectWithLength = readObjectForVarchar;
        varcharColumnParser.readObjectWithColumn = readObjectForFixchar;

        integerColumnParser.readObjectWithLength = NULL;
        integerColumnParser.readObjectWithColumn = readObjectForInteger;

        tinyintColumnParser.readObjectWithLength = NULL;
        tinyintColumnParser.readObjectWithColumn = readObjectForTinyInteger;

        smallintColumnParser.readObjectWithLength = NULL;
        smallintColumnParser.readObjectWithColumn = readObjectForSmallInteger;

        bigintColumnParser.readObjectWithLength = NULL;
        bigintColumnParser.readObjectWithColumn = readObjectForBigInteger;

        floatColumnParser.readObjectWithLength = NULL;
        floatColumnParser.readObjectWithColumn = readObjectForFloat;

        doubleColumnParser.readObjectWithLength = NULL;
        doubleColumnParser.readObjectWithColumn = readObjectForDouble;

        datetimeColumnParser.readObjectWithLength = NULL;
        datetimeColumnParser.readObjectWithColumn = readObjectForDatetime;

        hasInitialized = TRUE;
    }
}

static Type *readObjectForVarchar(ByteBuffer *byteBuffer, u32 length) {
    return byteBuffer->readString(byteBuffer, length);
}

static Type *readObjectForFixchar(ByteBuffer *byteBuffer, Column *column) {
    return byteBuffer->readString(byteBuffer, column->length);
}

static Type* readObjectForTinyInteger(ByteBuffer *byteBuffer, Column *column) {
    byte data = byteBuffer->readByte(byteBuffer);
    data = (byte) (data ^ (-1 << (SIZE_OF_BYTE * 8 - 1)));
    return createByte(data);
}

static Type* readObjectForSmallInteger(ByteBuffer *byteBuffer, Column *column) {
    short data = byteBuffer->readShort(byteBuffer);
    return createShort(data);
}

static Type* readObjectForInteger(ByteBuffer *byteBuffer, Column *column) {
    int data = byteBuffer->readInteger(byteBuffer);
    data = (data ^ (-1 << (SIZE_OF_INT * 8 - 1)));
    return createInteger(data);
}

static Type* readObjectForBigInteger(ByteBuffer *byteBuffer, Column *column) {
    long data = byteBuffer->readLong(byteBuffer);
    return createLong(data);
}

static Type* readObjectForFloat(ByteBuffer *byteBuffer, Column *column) {
    float data = byteBuffer->readFloat(byteBuffer);
    return createFloat(data);
}

static Type* readObjectForDouble(ByteBuffer *byteBuffer, Column *column) {
    double data = byteBuffer->readDouble(byteBuffer);
    return createDouble(data);
}

static Type* readObjectForDatetime(ByteBuffer *byteBuffer, Column *column) {
    u64 datetimeValue = byteBuffer->calcluateBigendian(byteBuffer, DATETIME_MAIN_SIZE);
    u16 second = (datetimeValue & 0x3FL);
    datetimeValue = datetimeValue>>6;
    u16 minute = (datetimeValue & 0x3FL);
    datetimeValue = datetimeValue>>6;
    u16 hour = (datetimeValue & 0x1FL);
    datetimeValue = datetimeValue>>5;
    u16 day = (datetimeValue & 0x1FL);
    datetimeValue = datetimeValue>>5;
    u32 yearAndMonth = (datetimeValue & 0x01FFFFL); 
    u16 year = yearAndMonth/13;
    u16 month = yearAndMonth%13;

    Datetime *datetime = NULL;

    if (column->precision==0) {
        datetime = createWithDatetime(year, month, day, hour, minute, second);
    }
    return datetime;
}