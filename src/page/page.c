#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "../common/type.h"
#include "../utils/utils.h"
#include "../common/constants.h"
#include "../data/objectType.h"
#include "../data/stringType.h"
#include "../data/arrayList.h"
#include "../data/hashMap.h"
#include "../table/table.h"

#include "byteBuffer.h"
#include "header.h"
#include "record.h"
#include "page.h"

static bool isLeafPage(IndexPage *this);

static bool isRootPage(IndexPage *this);

IndexPage *createIndexPage(FileHeader *fileHeader, FileTrailer *fileTrailer, ByteBuffer *byteBuffer, Table *table) {
    
    byteBuffer->setPosition(byteBuffer, FILE_HEADER_SIZE);
    IndexHeader *indexHeader = (IndexHeader *)malloc(sizeof(IndexHeader));
    initIndexHeader(byteBuffer, indexHeader);
    
    byteBuffer->setPosition(byteBuffer, FILE_HEADER_SIZE + INDEX_HEADER_SIZE);
    FileSegmentHeader *fsegHeader = (FileSegmentHeader *)malloc(sizeof(FileSegmentHeader));
    initFsegHeader(byteBuffer, fsegHeader);

    // infimum primaryKey offset in the page = 38 + 36 + 20 + 5 + 5 = 104
    u32 infimumHeaderPosition = FILE_HEADER_SIZE + INDEX_HEADER_SIZE + FSEG_HEADER_SIZE + RECORD_BUFFER_SIZE;
    byteBuffer->setPosition(byteBuffer, infimumHeaderPosition);
    DataRecord *infimum = readDataRecord(byteBuffer, table);

    // supremum primaryKey offset in the page = 38 + 36 + 20 + 5 + 8 + 5 + 5 = 117
    u32 supremumHeaderPosition = FILE_HEADER_SIZE + INDEX_HEADER_SIZE + FSEG_HEADER_SIZE + RECORD_BUFFER_SIZE + SYSTEM_MUM_RECORD_SIZE + RECORD_BUFFER_SIZE;
    byteBuffer->setPosition(byteBuffer, supremumHeaderPosition);
    DataRecord *supremum = readDataRecord(byteBuffer, table);

    IndexPage *indexPage = (IndexPage *)malloc(sizeof(IndexPage));
    indexPage->isLeafPage = isLeafPage;
    indexPage->isRootPage = isRootPage;
    indexPage->page.fileHeader = fileHeader;
    indexPage->page.fileTrailer = fileTrailer;
    indexPage->indexHeader = indexHeader;
    indexPage->fsegHeader = fsegHeader;
    indexPage->infimum = infimum;
    indexPage->supremum = supremum;

    Page *page = (Page *)indexPage;
    page->pageBuffer = byteBuffer;
    byteBuffer->setPosition(byteBuffer, infimum->getNextRecordPosition(infimum));

    u16 directorySlotCount = indexHeader->directorySlotCount;
    byteBuffer->setPosition(byteBuffer, PAGE_SIZE - FILE_TRAILER_SIZE - directorySlotCount*DIRECTORY_SLOT_SIZE);

    indexPage->directorySlotCount = directorySlotCount;
    indexPage->directorySlotList = (u16*)malloc(directorySlotCount*DIRECTORY_SLOT_SIZE);

    u32 i=0;
    for (i=0;i<directorySlotCount;++i) {
        indexPage->directorySlotList[directorySlotCount-i-1] = byteBuffer->readUnsignedShort(byteBuffer);;
    }

    return indexPage;
}

InodePage *createInodePage(FileHeader *fileHeader, FileTrailer *fileTrailer, ByteBuffer *byteBuffer) {
    return NULL;
}

FspHdrXesPage *createFspHdrXesPage(FileHeader *fileHeader, FileTrailer *fileTrailer, ByteBuffer *byteBuffer) {
    return NULL;
}

IBufBitmapPage *createIBufBitmapPage(FileHeader *fileHeader, FileTrailer *fileTrailer, ByteBuffer *byteBuffer) {
    return NULL;
}

static bool isLeafPage(IndexPage *this) {
    return (this->indexHeader->pageLevel==0);
}

static bool isRootPage(IndexPage *this) {
    Page *page = (Page *)this;
    FileHeader *fileHeader = page->fileHeader;
    return (fileHeader->prevPageNo==0 && fileHeader->nextPageNo==0);
}