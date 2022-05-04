
#define TRUE 					         1
#define FALSE 					         0
#define BIT_COUNT_PER_BYTE               8     

/*
 * Size Constants
 */
#define PAGE_SIZE                        16384

#define FILE_HEADER_SIZE                 38

#define FILE_TRAILER_SIZE                8

#define INDEX_HEADER_SIZE                36

#define FSEG_HEADER_SIZE                 20

#define RECORD_BUFFER_SIZE               5

#define SYSTEM_MUM_RECORD_SIZE           8

#define DIRECTORY_SLOT_SIZE              2

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

#define RECORD_CONVENTIONAL              0
#define RECORD_NODE_POINTER              1
#define RECORD_TYPE_INFIMUM              2
#define RECORD_TYPE_SUPREMUN             3

#define ROOT_PAGE_NUMBER                 3

#define TRANSACTION_ID_SIZE              6
#define ROLL_POINT_SIZE                  7
#define ROW_ID_SIZE                      6

#define TYPE_TINYINT                     "tinyint"
#define TYPE_SMALLINT                    "smallint"
#define TYPE_INT                         "int"
#define TYPE_BIGINT                      "bigint"
#define TYPE_FLOAT                       "float"
#define TYPE_DOUBLE                      "double"

#define TYPE_CHAR                        "char"
#define TYPE_BINARY                      "binary"
#define TYPE_VARCHAR                     "varchar"
#define TYPE_VARBINARY                   "varbinary"
#define TYPE_TINYBLOB                    "tinyblob"
#define TYPE_BLOB                        "blob"
#define TYPE_MEDIUMBLOB                  "mediumblob"
#define TYPE_LONGBLOB                    "longblob"
#define TYPE_TINYTEXT                    "tinytext"
#define TYPE_TEXT                        "text"
#define TYPE_MEDIUMTEXT                  "mediumtext"
#define TYPE_LONGTEXT                    "longtext"
#define TYPE_DATETIME                    "datetime"

#define MINIMUM_VALUE                    "minimum_value"
#define MAXIMUM_VALUE                    "maximum_value"