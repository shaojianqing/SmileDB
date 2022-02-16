typedef struct FileHeader FileHeader;

typedef struct FileTrailer FileTrailer;

typedef struct IndexHeader IndexHeader;

typedef struct FsegHeader FsegHeader;

typedef struct RecordHeader RecordHeader;

struct FileHeader {

    u32 checksum;

    u32 pageNumber;

    u32 prevPageNo;

    u32 nextPageNo;

    u64 lastModifiedLsn;

    u16 pageType;

    u64 flushLsn;

    u32 spaceId;
};

struct FileTrailer {
    u32 checksum;

    u32 low32lsn;
};

struct IndexHeader {
    u16 numOfDirSlots;

    u16 heapTopPosition;

    u16 indexPageFlag;

    u16 firstGarbageRecOffset;

    u16 garbageSpace;

    u16 lastInsertPos;

    u16 pageDirection;

    u16 numOfInsertsInPageDirection;

    u16 numOfRecords;

    u64 maxTransactionId;

    u16 pageLevel;

    u64 indexId;
};

struct FsegHeader {

    u32 leafPagesInodeSpace;

    u32 leafPagesInodePageNumber;

    u16 leafPagesInodeOffset;

    u32 nonLeafPagesInodeSpace;

    u32 nonLeafPagesInodePageNumber;

    u16 nonLeafPagesInodeOffset;
}

struct RecordHeader {

    
}

void initFileHeader(FileHeader *fileHeader);

void initFileTrailer(FileTrailer *fileTrailer);

void initIndexHeader(IndexHeader *indexHeader);

void initFsegHeader(FsegHeader *fsegHeader);