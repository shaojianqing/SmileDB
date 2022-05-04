
#include <stdio.h>
#include <stdlib.h>

#include "../common/constants.h"
#include "../common/type.h"
#include "../utils/utils.h"
#include "../data/objectType.h"
#include "../data/stringType.h"

#include "byteBuffer.h"
#include "header.h"

void initFileHeader(ByteBuffer *byteBuffer, FileHeader *fileHeader) {
    fileHeader->checksum = byteBuffer->readUnsignedInteger(byteBuffer);
    fileHeader->pageNumber = byteBuffer->readUnsignedInteger(byteBuffer);
    fileHeader->prevPageNo = byteBuffer->readUnsignedInteger(byteBuffer);
    fileHeader->nextPageNo = byteBuffer->readUnsignedInteger(byteBuffer);
    fileHeader->lastModifiedLsn = byteBuffer->readLong(byteBuffer);
    fileHeader->pageType = byteBuffer->readShort(byteBuffer);
    fileHeader->flushLsn = byteBuffer->readLong(byteBuffer);
    fileHeader->spaceId = byteBuffer->readUnsignedInteger(byteBuffer);
}

void initFileTrailer(ByteBuffer *byteBuffer, FileTrailer *fileTrailer) {
    fileTrailer->checksum = byteBuffer->readUnsignedInteger(byteBuffer);
    fileTrailer->low32lsn = byteBuffer->readUnsignedInteger(byteBuffer);
}

void initIndexHeader(ByteBuffer *byteBuffer, IndexHeader *indexHeader) {

    indexHeader->directorySlotCount = byteBuffer->readUnsignedShort(byteBuffer);
    indexHeader->heapTopPosition = byteBuffer->readUnsignedShort(byteBuffer);
    indexHeader->indexPageFlag = byteBuffer->readUnsignedShort(byteBuffer);
    indexHeader->firstGarbageRecOffset = byteBuffer->readUnsignedShort(byteBuffer);
    indexHeader->garbageSpace = byteBuffer->readUnsignedShort(byteBuffer);
    indexHeader->lastInsertPos = byteBuffer->readUnsignedShort(byteBuffer);
    indexHeader->pageDirection = byteBuffer->readUnsignedShort(byteBuffer);
    indexHeader->insertCountInPageDirection = byteBuffer->readUnsignedShort(byteBuffer);
    indexHeader->recordCount = byteBuffer->readUnsignedShort(byteBuffer);
    indexHeader->maxTransactionId = byteBuffer->readUnsignedLong(byteBuffer);
    indexHeader->pageLevel = byteBuffer->readUnsignedShort(byteBuffer);
    indexHeader->indexId = byteBuffer->readUnsignedLong(byteBuffer);
}

void initFsegHeader(ByteBuffer *byteBuffer, FileSegmentHeader *fsegHeader) {
    convertEndianInt(&(fsegHeader->leafPagesInodeSpace));
    convertEndianInt(&(fsegHeader->leafPagesInodePageNumber));
    convertEndianShort(&(fsegHeader->leafPagesInodeOffset));
    convertEndianInt(&(fsegHeader->nonLeafPagesInodeSpace));
    convertEndianInt(&(fsegHeader->nonLeafPagesInodePageNumber));
    convertEndianShort(&(fsegHeader->nonLeafPagesInodeOffset));
}

void initRecordHeader(ByteBuffer *byteBuffer, RecordHeader *recordHeader) { 

    byte minAndDelete = byteBuffer->readByte(byteBuffer);

    recordHeader->recordFlag = (minAndDelete & 0xf0)>>4;
    recordHeader->recordOwnedCount = (minAndDelete & 0x0f);

    u16 orderAndType = byteBuffer->readUnsignedShort(byteBuffer);

    recordHeader->recordType = (orderAndType & 0x07);
    recordHeader->order = (short)((orderAndType & 0xfff8)>>3);

    recordHeader->nextRecordOffset = byteBuffer->readShort(byteBuffer);
}