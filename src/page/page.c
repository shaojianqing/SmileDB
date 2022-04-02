#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "../common/type.h"
#include "../utils/utils.h"
#include "../common/constants.h"

#include "header.h"
#include "page.h"

IndexPage *createIndexPage(FileHeader *fileHeader, FileTrailer *fileTrailer, byte *buffer) {

    byte *indexHeaderBuf = buffer + FILE_HEADER_SIZE;
    IndexHeader *indexHeader = (IndexHeader *)malloc(INDEX_HEADER_SIZE);
    memcpy(indexHeader, indexHeaderBuf, INDEX_HEADER_SIZE);

    initIndexHeader(indexHeader);

    byte *fsegHeaderBuf = buffer + FILE_HEADER_SIZE + INDEX_HEADER_SIZE;
    FsegHeader *fsegHeader = (FsegHeader *)malloc(FSEG_HEADER_SIZE);
    memcpy(fsegHeader, fsegHeaderBuf, FSEG_HEADER_SIZE);

    initFsegHeader(fsegHeader);

    IndexPage *indexPage = (IndexPage *)malloc(sizeof(IndexPage));
    indexPage->page.fileHeader = fileHeader;
    indexPage->page.fileTrailer = fileTrailer;
    indexPage->indexHeader = indexHeader;
    indexPage->fsegHeader = fsegHeader;

    u16 directorySlotCount = indexHeader->directorySlotCount;
    byte *directorySlotBuf = buffer + PAGE_SIZE - directorySlotCount*DIRECTORY_SLOT_SIZE;

    indexPage->directorySlotCount = directorySlotCount;
    indexPage->directorySlotList = (u16*)malloc(directorySlotCount*DIRECTORY_SLOT_SIZE);

    int i=0;
    for (i=0;i<directorySlotCount;++i) {

        byte byte1 = directorySlotBuf[i*2];
        byte byte2 = directorySlotBuf[i*2+1];
        indexPage->directorySlotList[directorySlotCount-i-1] = (byte1<<2 && byte2);
    }

    return indexPage;
}

InodePage *createInodePage(FileHeader *fileHeader, FileTrailer *fileTrailer, byte *buffer) {

}

FspHdrXesPage *createFspHdrXesPage(FileHeader *fileHeader, FileTrailer *fileTrailer, byte *buffer) {

}

IBufBitmapPage *createIBufBitmapPage(FileHeader *fileHeader, FileTrailer *fileTrailer, byte *buffer) {

}