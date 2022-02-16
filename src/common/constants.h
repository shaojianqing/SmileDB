
/*
 * Size Constants
 */
#define PAGE_SIZE                        16384

#define FILE_HEADER_SIZE                 38
#define FILE_TRAILER_SIZE                8

/*
 * Page Type Enum
 */
#define PAGE_TYPE_ALLOCATED              0
#define PAGE_TYPE_UNDO_LOG               2
#define PAGE_TYPE_INODE                  3
#define PAGE_TYPE_IBUF_FREE_LIST         4
#define PAGE_TYPE_IBUF_BITMAP            5
#define PAGE_TYPE_SYSTEM                 6
#define PAGE_TYPE_TRX_SYSTEM             7
#define PAGE_TYPE_FILE_SPACE_HEADER      8
#define PAGE_TYPE_EXTENT_DESCRIPTOR      9
#define PAGE_TYPE_BLOB                   10
#define PAGE_TYPE_COMPRESSED_BLOB        11
#define PAGE_TYPE_COMPRESSED_BLOB2       12
#define PAGE_TYPE_UNKNOWN                13
#define PAGE_TYPE_RTREE_INDEX            17854
#define PAGE_TYPE_INDEX                  17855


