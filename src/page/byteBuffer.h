typedef struct ByteBuffer ByteBuffer;

struct ByteBuffer {

    byte *buffer;

    u32 bufferSize;

    u32 position;

    byte* (*readBuffer)(ByteBuffer *this, u32 start, u32 size);

    byte* (*readByteArray)(ByteBuffer *this, u32 size);

    byte (*readByte)(ByteBuffer *this);

    short (*readShort)(ByteBuffer *this);

    u16 (*readUnsignedShort)(ByteBuffer *this);

    int (*readInteger)(ByteBuffer *this);

    u32 (*readUnsignedInteger)(ByteBuffer *this);

    long (*readLong)(ByteBuffer *this);

    float (*readFloat)(ByteBuffer *this);

    double (*readDouble)(ByteBuffer *this);

    u64 (*readUnsignedLong)(ByteBuffer *this);

    String* (*readString)(ByteBuffer *this, u32 length);

    void (*increasePosition)(ByteBuffer *this, u32 delta);

    void (*decreasePosition)(ByteBuffer *this, u32 delta);

    void (*setPosition)(ByteBuffer *this, u32 position);

    u32 (*getPosition)(ByteBuffer *this);
};

ByteBuffer* constructByteBuffer(byte *buffer, u32 size);