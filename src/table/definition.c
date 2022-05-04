#include <stdlib.h>
#include <stdio.h>

#include "../common/constants.h"
#include "../common/type.h"
#include "../data/objectType.h"
#include "../data/stringType.h"
#include "../data/arrayList.h"
#include "../data/hashMap.h"

#include "table.h"
#include "definition.h"

static Table orderInfoTable;

static Table customerInfoTable;

static List* initCustomerInfoColumnName(Table *table);

static List* initCustomerInfoColumnList(Table *table);

static List* initCustomerInfoKeyColumnList(Table *table);

static List* initCustomerInfoKeyVarLenColumnList(Table *table);

static List* initCustomerInfoNullableColumnList(Table *table);

static List* initCustomerInfoVariableLenColumnList(Table *table);

Table* initOrderInfoTableDefinition() {

    return &orderInfoTable;
}

Table* initCustomerInfoTableDefinition() {
    customerInfoTable.name = createString("customer_info");
    
    customerInfoTable.columnNames = initCustomerInfoColumnName(&customerInfoTable);
    customerInfoTable.columnList = initCustomerInfoColumnList(&customerInfoTable);
    customerInfoTable.keyColumnList = initCustomerInfoKeyColumnList(&customerInfoTable);
    customerInfoTable.keyVarLenColumnList = initCustomerInfoKeyVarLenColumnList(&customerInfoTable);
    customerInfoTable.nullableColumnList = initCustomerInfoNullableColumnList(&customerInfoTable);
    customerInfoTable.variableLenColumnList = initCustomerInfoVariableLenColumnList(&customerInfoTable);

    return &customerInfoTable;
}

static List* initCustomerInfoColumnName(Table *table) {
    List *columnNames = createArrayList(8);
    columnNames->add(columnNames, createString("customer_id"));
    columnNames->add(columnNames, createString("customer_name"));
    columnNames->add(columnNames, createString("customer_gender"));
    columnNames->add(columnNames, createString("customer_identifier"));
    columnNames->add(columnNames, createString("customer_job"));
    columnNames->add(columnNames, createString("customer_country"));
    columnNames->add(columnNames, createString("customer_province"));
    columnNames->add(columnNames, createString("customer_city"));
    columnNames->add(columnNames, createString("customer_birthday"));
    columnNames->add(columnNames, createString("customer_description"));
    columnNames->add(columnNames, createString("create_time"));
    columnNames->add(columnNames, createString("update_time"));
    return columnNames;
}

static List* initCustomerInfoColumnList(Table *table) {
    List *columnList = createArrayList(8);

    Column *column = buildColumn(table, createString("customer_id"), createString("varchar"), FALSE, TRUE, 36);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_name"), createString("varchar"), FALSE, TRUE, 32);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_gender"), createString("varchar"), FALSE, TRUE, 20);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_identifier"), createString("varchar"), FALSE, TRUE, 40);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_job"), createString("varchar"), FALSE, TRUE, 20);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_country"), createString("varchar"), FALSE, TRUE, 32);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_province"), createString("varchar"), FALSE, TRUE, 32);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_city"), createString("varchar"), FALSE, TRUE, 30);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_birthday"), createString("varchar"), FALSE, TRUE, 20);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_description"), createString("varchar"), FALSE, TRUE, 88);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("create_time"), createString("datetime"), FALSE, TRUE, 8);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("update_time"), createString("datetime"), FALSE, TRUE, 8);
    columnList->add(columnList, column);
    return columnList;
}

static List* initCustomerInfoNullableColumnList(Table *table) {
    List *nullableColumnList = createArrayList(8);
    return nullableColumnList;
}

static List* initCustomerInfoKeyColumnList(Table *table) {
    List *keyColumnList = createArrayList(2);
    Column *column = buildColumn(table, createString("customer_id"), createString("varchar"), FALSE, TRUE, 36);
    keyColumnList->add(keyColumnList, column);
    return keyColumnList;
}

static List* initCustomerInfoKeyVarLenColumnList(Table *table) {
    List *keyVarLenColumnList = createArrayList(2);
    Column *column = buildColumn(table, createString("customer_id"), createString("varchar"), FALSE, TRUE, 36);
    keyVarLenColumnList->add(keyVarLenColumnList, column);
    return keyVarLenColumnList;
}

static List* initCustomerInfoVariableLenColumnList(Table *table) {
    List *variableLenColumnList = createArrayList(8);
    Column *column = buildColumn(table, createString("customer_id"), createString("varchar"), FALSE, TRUE, 36);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_name"), createString("varchar"), FALSE, TRUE, 32);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_gender"), createString("varchar"), FALSE, TRUE, 20);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_identifier"), createString("varchar"), FALSE, TRUE, 40);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_job"), createString("varchar"), FALSE, TRUE, 20);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_country"), createString("varchar"), FALSE, TRUE, 32);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_province"), createString("varchar"), FALSE, TRUE, 32);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_city"), createString("varchar"), FALSE, TRUE, 30);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_birthday"), createString("varchar"), FALSE, TRUE, 20);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_description"), createString("varchar"), FALSE, TRUE, 88);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("create_time"), createString("datetime"), FALSE, TRUE, 8);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("update_time"), createString("datetime"), FALSE, TRUE, 8);
    variableLenColumnList->add(variableLenColumnList, column);
    return variableLenColumnList;
}