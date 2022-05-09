#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/type.h"
#include "../data/objectType.h"
#include "../data/stringType.h"
#include "../utils/utils.h"

#include "byteBuffer.h"

static byte* readBuffer(ByteBuffer *this, u32 start, u32 size);

static byte* readByteArray(ByteBuffer *this, u32 size);

static byte readByte(ByteBuffer *this);

static short readShort(ByteBuffer *this);

static u16 readUnsignedShort(ByteBuffer *this);

static int readInteger(ByteBuffer *this);

static u32 readUnsignedInteger(ByteBuffer *this);

static long readLong(ByteBuffer *this);

static u64 readUnsignedLong(ByteBuffer *this);

static float readFloat(ByteBuffer *this);

static double readDouble(ByteBuffer *this);

static String* readString(ByteBuffer *this, u32 length);

static u64 calcluateBigendian(ByteBuffer *this, u32 length);

static void increasePosition(ByteBuffer *this, u32 delta);

static void decreasePosition(ByteBuffer *this, u32 delta);

static void setPosition(ByteBuffer *this, u32 position);

static u32 getPosition(ByteBuffer *this);

ByteBuffer *constructByteBuffer(byte *buffer, u32 size) {

    ByteBuffer *byteBuffer = (ByteBuffer *)malloc(sizeof(ByteBuffer));
    byteBuffer->buffer = buffer;
    byteBuffer->bufferSize = size;
    byteBuffer->position = 0;

    byteBuffer->readBuffer = readBuffer;
    byteBuffer->readByteArray = readByteArray;
    byteBuffer->readByte = readByte;
    byteBuffer->readShort = readShort;
    byteBuffer->readUnsignedShort = readUnsignedShort;
    byteBuffer->readInteger = readInteger;
    byteBuffer->readUnsignedInteger = readUnsignedInteger;
    byteBuffer->readLong = readLong;
    byteBuffer->readUnsignedLong = readUnsignedLong;
    byteBuffer->readFloat = readFloat;
    byteBuffer->readDouble = readDouble;
    byteBuffer->readString = readString;
    byteBuffer->calcluateBigendian =calcluateBigendian;
    byteBuffer->increasePosition = increasePosition;
    byteBuffer->decreasePosition = decreasePosition;
    byteBuffer->setPosition = setPosition;
    byteBuffer->getPosition = getPosition;

    return byteBuffer;
}

static byte* readBuffer(ByteBuffer *this, u32 start, u32 size) {
    u32 bufferSize = this->bufferSize;
    if (start+size > bufferSize) {
        printf("ReadBuffer Raise Error!start:%u, size:%u\n", start, size);
        exit(1);
    }

    byte* allocBuffer = (byte *)malloc(size);
    memcpy(allocBuffer, (byte*)(this->buffer+start), size);
    return allocBuffer;
}

static byte* readByteArray(ByteBuffer *this, u32 size) {
    u32 bufferSize = this->bufferSize;
    if (this->position + size > bufferSize) {
        printf("ReadBuffer Raise Error!position:%u, size:%u\n", this->position, size);
        exit(1);
    }
    
    byte* allocBuffer = (byte *)malloc(size);
    memcpy(allocBuffer, (byte*)(this->buffer + this->position), size);
    this->position += size;
    return allocBuffer;
}

static byte readByte(ByteBuffer *this) {
    byte *valueBuf = (byte *)(this->buffer + this->position);
    byte value = *valueBuf;
    this->position += sizeof(byte);
    return value;
}

static short readShort(ByteBuffer *this) {
    short *valueBuf = (short *)(this->buffer + this->position);
    short value = *valueBuf;
    convertEndianShort2(&value);
    this->position += sizeof(short);
    return value;
}

static u16 readUnsignedShort(ByteBuffer *this) {
    u16 *valueBuf = (u16 *)(this->buffer + this->position);
    u16 value = *valueBuf;
    convertEndianShort(&value);
    this->position += sizeof(u16);
    return value;
}

static int readInteger(ByteBuffer *this) {
    int *valueBuf = (int *)(this->buffer + this->position);
    int value = *valueBuf;
    convertEndianInt2(&value);
    this->position += sizeof(int);
    return value;
}

static u32 readUnsignedInteger(ByteBuffer *this) {
    u32 *valueBuf = (u32 *)(this->buffer + this->position);
    u32 value = *valueBuf;
    convertEndianInt(&value);
    this->position += sizeof(u32);
    return value;
}

static long readLong(ByteBuffer *this) {
    long *valueBuf = (long *)(this->buffer + this->position);
    long value = *valueBuf;
    convertEndianLong2(&value);
    this->position += sizeof(long);
    return value;
}

static u64 readUnsignedLong(ByteBuffer *this) {
    u64 *valueBuf = (u64 *)(this->buffer + this->position);
    u64 value = *valueBuf;
    convertEndianLong(&value);
    this->position += sizeof(u64);
    return value;
}

static float readFloat(ByteBuffer *this) {
    FloatByte floatByte;
    memcpy(&floatByte, (this->buffer + this->position), sizeof(float));
    this->position += sizeof(float);
    convertEndianFloat(&floatByte.value);
    return floatByte.value;
}

static double readDouble(ByteBuffer *this) {
    DoubleByte doubleByte;
    memcpy(&doubleByte, (this->buffer + this->position), sizeof(double));
    this->position += sizeof(double);
    convertEndianDouble(&doubleByte.value);
    return doubleByte.value;
}

static String* readString(ByteBuffer *this, u32 length) {
    char *value = (char *) malloc(length+1);
    memcpy(value, (char *)(this->buffer + this->position), length);
    this->position += length;
    value[length] = 0;

    return createString(value);
}

static u64 calcluateBigendian(ByteBuffer *this, u32 length) {
    byte* bytes = this->readByteArray(this, length);
    long val = 0;
    int i = length;
    int s = 0;
    while (i != 0) {
      i--;
      long v = (bytes[i] & 0xffL);
      val += (v << s);
      s += 8;
    }
    return val;

    /*byte* datetimeBuf = this->readByteArray(this, length);
    u64 result = 0;
    u32 i = 0;
    for (i=0;i<length;++i) {
       result += (datetimeBuf[i] && 0xFF);
       result = (result<<8);
    }
    return result;*/
}

static void increasePosition(ByteBuffer *this, u32 delta) {

    if (this->position + delta >= this->bufferSize) {
        printf("IncreasePosition Raise Error!position:%u,delta:%u\n", this->position, delta);
        exit(1);
    }
    this->position += delta;
}

static void decreasePosition(ByteBuffer *this, u32 delta) {

    if (this->position<delta) {
        printf("DecreasePosition Raise Error!position:%u,delta:%u\n", this->position, delta);
        exit(1);
    }
    this->position -= delta;
}

static void setPosition(ByteBuffer *this, u32 position) {
    this->position = position;
}

static u32 getPosition(ByteBuffer *this) {
    return this->position;
}