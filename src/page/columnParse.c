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
#include "../data/arrayList.h"
#include "../data/hashMap.h"
#include "../table/table.h"

#include "byteBuffer.h"
#include "columnParse.h"

static bool hasInitialized = FALSE;

static ColumnParser varcharColumnParser;

static ColumnParser integerColumnParser;

static ColumnParser tinyintColumnParser;

static ColumnParser smallintColumnParser;

static ColumnParser integerColumnParser;

static ColumnParser bigintColumnParser;

static ColumnParser floatColumnParser;

static ColumnParser doubleColumnParser;

static ColumnParser datetimeColumnParser;

static void initializeColumnParser();

static Type *readObjectForVarchar(ByteBuffer *byteBuffer, u32 length);

static Type *readObjectForFixchar(ByteBuffer *byteBuffer, Column *column);

static Type* readObjectForInteger(ByteBuffer *byteBuffer, Column *column);

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
    return createByte(data);
}

static Type* readObjectForSmallInteger(ByteBuffer *byteBuffer, Column *column) {
    short data = byteBuffer->readShort(byteBuffer);
    return createShort(data);
}

static Type* readObjectForInteger(ByteBuffer *byteBuffer, Column *column) {
    int data = byteBuffer->readInteger(byteBuffer);
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
    return NULL;
}