
typedef struct DataRecord DataRecord;

typedef struct VarLenInfo VarLenInfo;

struct VarLenInfo {

    String *columnName;

    u16 columnLength;

    bool isOverflowPage;
};

struct DataRecord {

    RecordHeader *header;

    int primaryKeyPosition;

    Table *table;

    HashMap *recordData;

    u32 fieldCount;

    u64 childPageNumber;

    List* (*getPrimaryKeyValues)(DataRecord *this);

    int (*getNextRecordPosition)(DataRecord *this);

    Type* (*getObject)(DataRecord *this, String *cloumnName);

    void (*putObject)(DataRecord *this, String *cloumnName, Type *columnValue);
};

DataRecord* constructDataRecord(RecordHeader *header, Table *table);

DataRecord* readDataRecord(ByteBuffer *byteBuffer, Table *table);

bool VarLenInfoEqualFun(Type *obj1, Type *obj2);