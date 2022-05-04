
typedef struct List List;

typedef struct Object Object;

typedef struct String String;

typedef struct Table Table;

typedef struct Column Column;

struct Column {

    Object super;

    Table *table;

    String *name;

    String *type;

    bool nullable;

    bool isPrimaryKey;

    int length;

    int scale;

    int precision;

    bool (*isFixedLength)(Column *column);

    bool (*isVariableLength)(Column *column);
};

struct Table {

    String *name;

    List *columnNames;

    List *columnList;

    List *keyColumnList;

    List *keyVarLenColumnList;

    List *nullableColumnList;

    List *variableLenColumnList;
};

Column *buildColumn(Table *table, String *name, String *type, bool nullable, bool isPrimaryKey, int length);