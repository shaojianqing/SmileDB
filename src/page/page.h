
typedef struct Page Page;

typedef struct IndexPage IndexPage;

typedef struct InodePage InodePage;

typedef struct FspHdrXesPage FspHdrXesPage;

typedef struct IBufBitmapPage IBufBitmapPage;

struct Page {

    FileHeader *fileHeader;

    FileTrailer *fileTrailer;

    ByteBuffer *pageBuffer;
};

struct IndexPage {
    Page page;

    IndexHeader *indexHeader;

    FileSegmentHeader *fsegHeader;

    DataRecord *infimum;

    DataRecord *supremum;

    u16* directorySlotList;

    u16 directorySlotCount;

    bool (*isLeafPage)(IndexPage *this);

    bool (*isRootPage)(IndexPage *this);
};

struct InodePage {
    Page page;

};

struct FspHdrXesPage {
    Page page;

};

struct IBufBitmapPage {
    Page page;

};

IndexPage *createIndexPage(FileHeader *fileHeader, FileTrailer *fileTrailer, ByteBuffer *byteBuffer, Table *table);

InodePage *createInodePage(FileHeader *fileHeader, FileTrailer *fileTrailer, ByteBuffer *byteBuffer);

FspHdrXesPage *createFspHdrXesPage(FileHeader *fileHeader, FileTrailer *fileTrailer, ByteBuffer *byteBuffer);

IBufBitmapPage *createIBufBitmapPage(FileHeader *fileHeader, FileTrailer *fileTrailer, ByteBuffer *byteBuffer);