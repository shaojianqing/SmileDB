
typedef struct Table Table;

typedef struct Column Column;

typedef struct KeyMeta KeyMeta;

struct Column {

    Table *table;

    char *name;

    int ordinal;

    char *type;

    bool nullable;

    bool isPrimaryKey;

    int length;

    int scale;

    int precision;
}