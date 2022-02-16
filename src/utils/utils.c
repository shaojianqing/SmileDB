
#include <stdio.h>
#include <stdlib.h>

#include "../common/type.h"

#include "utils.h"

void convertEndianShort(u16 *data) {
    byte *buffer = (byte*)data;
    byte byte0 = buffer[0];
    byte byte1 = buffer[1];

    buffer[0] = byte1;
    buffer[1] = byte0;
}

void convertEndianInt(u32 *data) {
    byte *buffer = (byte*)data;
    byte byte0 = buffer[0];
    byte byte1 = buffer[1];
    byte byte2 = buffer[2];
    byte byte3 = buffer[3];

    buffer[0] = byte3;
    buffer[1] = byte2;
    buffer[2] = byte1;
    buffer[3] = byte0;
}

void convertEndianLong(u64 *data) {
    byte *buffer = (byte*)data;
    byte byte0 = buffer[0];
    byte byte1 = buffer[1];
    byte byte2 = buffer[2];
    byte byte3 = buffer[3];
    byte byte4 = buffer[4];
    byte byte5 = buffer[5];
    byte byte6 = buffer[6];
    byte byte7 = buffer[7];

    buffer[0] = byte7;
    buffer[1] = byte6;
    buffer[2] = byte5;
    buffer[3] = byte4;
    buffer[4] = byte3;
    buffer[5] = byte2;
    buffer[6] = byte1;
    buffer[7] = byte0;
}