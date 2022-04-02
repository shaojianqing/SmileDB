#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "../common/type.h"
#include "../utils/utils.h"
#include "../common/constants.h"
#include "../page/header.h"
#include "../page/page.h"
#include "storage.h"

Page* loadPage(File* file, u32 pageNumber) {
    byte *buffer = (byte*)malloc(PAGE_SIZE);
    fseek(file, PAGE_SIZE*pageNumber, SEEK_SET);
    fread(buffer, 1, PAGE_SIZE, file);

    byte *fileHeaderBuf = buffer;
    FileHeader *fileHeader = (FileHeader*)malloc(FILE_HEADER_SIZE);
    memcpy(fileHeader, fileHeaderBuf, FILE_HEADER_SIZE);

    initFileHeader(fileHeader);

    byte *fileTrailerBuf = (buffer + PAGE_SIZE - FILE_TRAILER_SIZE);
    FileTrailer *fileTrailer = (FileTrailer*)malloc(FILE_TRAILER_SIZE);
    memcpy(fileTrailer, fileTrailerBuf, FILE_TRAILER_SIZE);

    initFileTrailer(fileTrailer);

    u16 pageType = page->fileHeader->pageType;
    if (pageType == PAGE_TYPE_FILE_SPACE_HEADER) {
        return (Page *)createIndexPage(fileHeader, fileTrailer, buffer);
    } else if (pageType == PAGE_TYPE_EXTENT_DESCRIPTOR) {

    } else if (pageType == PAGE_TYPE_IBUF_BITMAP) {
        return (Page *)createInodePage(fileHeader, fileTrailer, buffer);
    } else if (pageType == PAGE_TYPE_INDEX) {
        return (Page *)createFspHdrXesPage(fileHeader, fileTrailer, buffer);
    } else if (pageType == PAGE_TYPE_INODE) {
        return (Page *)createIBufBitmapPage(fileHeader, fileTrailer, buffer);
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