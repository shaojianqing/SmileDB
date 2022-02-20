
#include <stdio.h>
#include <stdlib.h>

#include "../common/type.h"
#include "../utils/utils.h"

#include "header.h"

void initFileHeader(FileHeader *fileHeader) {
    convertEndianInt(&(fileHeader->checksum));
    convertEndianInt(&(fileHeader->pageNumber));
    convertEndianInt(&(fileHeader->prevPageNo));
    convertEndianInt(&(fileHeader->nextPageNo));

    convertEndianLong(&(fileHeader->lastModifiedLsn));
    convertEndianShort(&(fileHeader->pageType));
    convertEndianLong(&(fileHeader->flushLsn));
    convertEndianInt(&(fileHeader->spaceId));
}

void initFileTrailer(FileTrailer *fileTrailer) {
    convertEndianInt(&(fileTrailer->checksum));
    convertEndianInt(&(fileTrailer->low32lsn));
}

void initIndexHeader(IndexHeader *indexHeader) {
    convertEndianShort(&(indexHeader->numOfDirSlots));
    convertEndianShort(&(indexHeader->heapTopPosition));
    convertEndianShort(&(indexHeader->indexPageFlag));
    convertEndianShort(&(indexHeader->firstGarbageRecOffset));
    convertEndianShort(&(indexHeader->garbageSpace));
    convertEndianShort(&(indexHeader->lastInsertPos));
    convertEndianShort(&(indexHeader->pageDirection));
    convertEndianShort(&(indexHeader->numOfInsertsInPageDirection));
    convertEndianShort(&(indexHeader->numOfRecords));
    convertEndianLong(&(indexHeader->maxTransactionId));
    convertEndianShort(&(indexHeader->pageLevel));
    convertEndianLong(&(indexHeader->indexId));
}

void initFsegHeader(FsegHeader *fsegHeader) {
    convertEndianInt(&(fsegHeader->leafPagesInodeSpace));
    convertEndianInt(&(fsegHeader->leafPagesInodePageNumber));
    convertEndianShort(&(fsegHeader->leafPagesInodeOffset));
    convertEndianInt(&(fsegHeader->nonLeafPagesInodeSpace));
    convertEndianInt(&(fsegHeader->nonLeafPagesInodePageNumber));
    convertEndianShort(&(fsegHeader->nonLeafPagesInodeOffset));
}