
typedef struct Page Page;

typedef struct IndexPage IndexPage;

typedef struct InodePage INodePage;

typedef struct FspHdrXesPage FspHdrXesPage;

typedef struct IBufBitmapPage IBufBitmapPage;

struct Page {
    FileHeader *fileHeader;

    FileTrailer *fileTrailer;

    byte *pageBuffer;
};

struct IndexPage {
    Page page;

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







