
typedef struct DataRecord DataRecord;

struct DataRecord {

    u64 pageNumber;

    RecordHeader *header;

    int primaryKeyPosition;

    Table *table;

    Object *fieldDatas;

    u32 fieldSize;

    u64 childPageNumber;
}