#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "common/type.h"
#include "utils/utils.h"
#include "common/constants.h"
#include "page/header.h"
#include "page/page.h"
#include "storage/storage.h"

int main(int argc, char **argv) {

    File *customInfoFile = fopen("/Users/shaojianqing/customer_info.ibd","rw");

    if (customInfoFile!=NULL) {
        u32 pageCount = calculatePageCount(customInfoFile);
        printf("Hello, CustomInfoDB PageCount:%d\n\n", pageCount);

        Page *page = loadPage(customInfoFile, 27);

        printf("Hello, CustomInfoDB PageType:%d\n\n", page->fileHeader->pageType);

        printf("Hello, CustomInfoDB PageNumber:%d\n\n", page->fileHeader->pageNumber);
    }

    fclose(customInfoFile);

    printf("Hello, Shaojianqing->SmileDB\n");
}