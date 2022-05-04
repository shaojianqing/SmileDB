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
#include "../page/byteBuffer.h"
#include "../page/header.h"
#include "../table/table.h"
#include "../page/record.h"
#include "../page/page.h"

#include "storage.h"

Page* loadPage(File* file, u32 pageNumber, Table *table) {
    byte *buffer = (byte*)malloc(PAGE_SIZE);
    fseek(file, PAGE_SIZE*pageNumber, SEEK_SET);
    fread(buffer, 1, PAGE_SIZE, file);

    ByteBuffer *byteBuffer = constructByteBuffer(buffer, PAGE_SIZE);

    byteBuffer->setPosition(byteBuffer, 0);
    FileHeader *fileHeader = (FileHeader*)malloc(sizeof(FileHeader));
    initFileHeader(byteBuffer, fileHeader);

    byteBuffer->setPosition(byteBuffer, PAGE_SIZE - FILE_TRAILER_SIZE);
    FileTrailer *fileTrailer = (FileTrailer*)malloc(sizeof(FileTrailer));
    initFileTrailer(byteBuffer, fileTrailer);

    u16 pageType = fileHeader->pageType;
    if (pageType == PAGE_TYPE_INDEX) {
        return (Page *)createIndexPage(fileHeader, fileTrailer, byteBuffer, table);
    } else if (pageType == PAGE_TYPE_EXTENT_DESCRIPTOR) {

    } else if (pageType == PAGE_TYPE_INODE) {
        return (Page *)createInodePage(fileHeader, fileTrailer, byteBuffer);
    } else if (pageType == PAGE_TYPE_FILE_SPACE_HEADER) {
        return (Page *)createFspHdrXesPage(fileHeader, fileTrailer, byteBuffer);
    } else if (pageType == PAGE_TYPE_IBUF_BITMAP) {
        return (Page *)createIBufBitmapPage(fileHeader, fileTrailer, byteBuffer);
    }

    return NULL;
}

u32 calculatePageCount(File* file) {
    if (file!=NULL) {
        fseek(file, 0, SEEK_END);
		u32 length = ftell(file);
        return (length/PAGE_SIZE);
    }
    return 0;
}