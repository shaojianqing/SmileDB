
typedef struct ColumnParser ColumnParser;

struct ColumnParser {

    Type* (*readObjectWithLength)(ByteBuffer *byteBuffer, u32 length);

    Type* (*readObjectWithColumn)(ByteBuffer *byteBuffer, Column *column);
};

ColumnParser* constructColumnParser(String *columnType);