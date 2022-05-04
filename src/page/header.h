typedef struct FileHeader FileHeader;

typedef struct FileTrailer FileTrailer;

typedef struct IndexHeader IndexHeader;

typedef struct FileSegmentHeader FileSegmentHeader;

typedef struct FileSpaceHeader FileSpaceHeader;

typedef struct RecordHeader RecordHeader;

typedef struct ListBaseNode ListBaseNode;

typedef struct ListExtentNode ListExtentNode;

typedef struct ExtentDescriptor ExtentDescriptor;

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

    u16 directorySlotCount;

    u16 heapTopPosition;

    u16 indexPageFlag;

    u16 firstGarbageRecOffset;

    u16 garbageSpace;

    u16 lastInsertPos;

    u16 pageDirection;

    u16 insertCountInPageDirection;

    u16 recordCount;

    u64 maxTransactionId;

    u16 pageLevel;

    u64 indexId;
};

struct FileSegmentHeader {

    u32 leafPagesInodeSpace;

    u32 leafPagesInodePageNumber;

    u16 leafPagesInodeOffset;

    u32 nonLeafPagesInodeSpace;

    u32 nonLeafPagesInodePageNumber;

    u16 nonLeafPagesInodeOffset;
};

struct ListBaseNode {

    u32 length;

    int firstPageNo;

    u16 firstPageOffset;

    int lastPageNo;

    u16 lastPageOffset;
};

struct FileSpaceHeader {

    u64 spaceId;

    u64 size;

    u64 freeLimit;

    u64 flags;

    u64 usedPageCount;

    ListBaseNode free;

    ListBaseNode freeFrag;

    ListBaseNode fullFrag;

    long nextUsedSegmentId;

    ListBaseNode fullInodes;

    ListBaseNode freeInodes;
};

struct ListExtentNode {

    int prevPageNo;

    short prevOffset;

    int nextPageNo;

    short nextOffset; 
};

struct ExtentDescriptor {

    u64 segmentId;

    ListExtentNode extentNode;

    u32 state;

    //byte[16] pageStateBitmap;
};

struct RecordBuffer {

    u8 minAndDelete;

    u16 orderAndType;

    short nextOffest;
};

struct RecordHeader {

    u8 recordFlag;

    u16 recordOwnedCount;

    short order;

    u16 recordType;

    int nextRecordOffset;
};

void initFileHeader(ByteBuffer *byteBuffer, FileHeader *fileHeader);

void initFileTrailer(ByteBuffer *byteBuffer, FileTrailer *fileTrailer);

void initIndexHeader(ByteBuffer *byteBuffer, IndexHeader *indexHeader);  

void initFsegHeader(ByteBuffer *byteBuffer, FileSegmentHeader *fsegHeader);

void initRecordHeader(ByteBuffer *byteBuffer, RecordHeader *recordHeader);