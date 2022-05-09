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

static List* initOrderInfoColumnName(Table *table);

static List* initOrderInfoColumnList(Table *table);

static List* initOrderInfoKeyColumnList(Table *table);

static List* initOrderInfoKeyVarLenColumnList(Table *table);

static List* initOrderInfoNullableColumnList(Table *table);

static List* initOrderInfoVariableLenColumnList(Table *table);

static List* initCustomerInfoColumnName(Table *table);

static List* initCustomerInfoColumnList(Table *table);

static List* initCustomerInfoKeyColumnList(Table *table);

static List* initCustomerInfoKeyVarLenColumnList(Table *table);

static List* initCustomerInfoNullableColumnList(Table *table);

static List* initCustomerInfoVariableLenColumnList(Table *table);

Table* initOrderInfoTableDefinition() {
    orderInfoTable.name = createString("order_info");

    orderInfoTable.columnNames = initOrderInfoColumnName(&orderInfoTable);
    orderInfoTable.columnList = initOrderInfoColumnList(&orderInfoTable);
    orderInfoTable.keyColumnList = initOrderInfoKeyColumnList(&customerInfoTable);
    orderInfoTable.keyVarLenColumnList = initOrderInfoKeyVarLenColumnList(&customerInfoTable);
    orderInfoTable.nullableColumnList = initOrderInfoNullableColumnList(&customerInfoTable);
    orderInfoTable.variableLenColumnList = initOrderInfoVariableLenColumnList(&customerInfoTable);

    return &orderInfoTable;
}

static List* initOrderInfoColumnName(Table *table) {
    List *columnNames = createArrayList(8);
    columnNames->add(columnNames, createString("order_id"));
    columnNames->add(columnNames, createString("product_id"));
    columnNames->add(columnNames, createString("product_name"));
    columnNames->add(columnNames, createString("unit_price"));
    columnNames->add(columnNames, createString("currency"));
    columnNames->add(columnNames, createString("quantity"));
    columnNames->add(columnNames, createString("service_fee"));
    columnNames->add(columnNames, createString("consumer_id"));
    columnNames->add(columnNames, createString("consumer_name"));
    columnNames->add(columnNames, createString("merchant_id"));
    columnNames->add(columnNames, createString("merchant_name"));
    columnNames->add(columnNames, createString("order_description"));
    columnNames->add(columnNames, createString("is_valid"));
    columnNames->add(columnNames, createString("gmt_create"));
    columnNames->add(columnNames, createString("gmt_modified"));
    return columnNames;
}

static List* initOrderInfoColumnList(Table *table) {

    List *columnList = createArrayList(8);
    Column *column = buildColumn(table, createString("order_id"), createString("varchar"), FALSE, TRUE, 36, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("product_id"), createString("varchar"), FALSE, FALSE, 36, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("product_name"), createString("varchar"), FALSE, FALSE, 100, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("unit_price"), createString("double"), FALSE, FALSE, 8, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("currency"), createString("varchar"), FALSE, FALSE, 20, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("quantity"), createString("int"), FALSE, FALSE, 4, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("service_fee"), createString("double"), FALSE, FALSE, 8, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("consumer_id"), createString("varchar"), FALSE, FALSE, 36, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("consumer_name"), createString("varchar"), FALSE, FALSE, 32, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("merchant_id"), createString("varchar"), FALSE, FALSE, 36, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("merchant_name"), createString("varchar"), FALSE, FALSE, 32, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("order_description"), createString("varchar"), FALSE, FALSE, 100, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("is_valid"), createString("tinyint"), FALSE, FALSE, 1, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("gmt_create"), createString("datetime"), FALSE, FALSE, 5, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("gmt_modified"), createString("datetime"), FALSE, FALSE, 5, 0);
    columnList->add(columnList, column);
    return columnList;
}

static List* initOrderInfoKeyColumnList(Table *table) {
     List *keyColumnList = createArrayList(2);
    Column *column = buildColumn(table, createString("order_id"), createString("varchar"), FALSE, TRUE, 36, 0);
    keyColumnList->add(keyColumnList, column);
    return keyColumnList;
}

static List* initOrderInfoKeyVarLenColumnList(Table *table) {
    List *keyVarLenColumnList = createArrayList(2);
    Column *column = buildColumn(table, createString("order_id"), createString("varchar"), FALSE, TRUE, 36, 0);
    keyVarLenColumnList->add(keyVarLenColumnList, column);
    return keyVarLenColumnList;
}

static List* initOrderInfoNullableColumnList(Table *table) {
    List *nullableColumnList = createArrayList(8);
    Column *column = buildColumn(table, createString("order_description"), createString("varchar"), TRUE, FALSE, 100, 0);
    nullableColumnList->add(nullableColumnList, column);
    return nullableColumnList;
}

static List* initOrderInfoVariableLenColumnList(Table *table) {
    List *columnList = createArrayList(8);
    Column *column = buildColumn(table, createString("order_id"), createString("varchar"), FALSE, TRUE, 36, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("product_id"), createString("varchar"), FALSE, FALSE, 36, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("product_name"), createString("varchar"), FALSE, FALSE, 100, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("currency"), createString("varchar"), FALSE, FALSE, 20, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("consumer_id"), createString("varchar"), FALSE, FALSE, 36, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("consumer_name"), createString("varchar"), FALSE, FALSE, 32, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("merchant_id"), createString("varchar"), FALSE, FALSE, 36, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("merchant_name"), createString("varchar"), FALSE, FALSE, 32, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("order_description"), createString("varchar"), TRUE, FALSE, 100, 0);
    columnList->add(columnList, column);
    return columnList;
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

    Column *column = buildColumn(table, createString("customer_id"), createString("varchar"), FALSE, TRUE, 36, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_name"), createString("varchar"), FALSE, FALSE, 32, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_gender"), createString("varchar"), FALSE, FALSE, 20, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_identifier"), createString("varchar"), FALSE, FALSE, 40, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_job"), createString("varchar"), FALSE, FALSE, 20, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_country"), createString("varchar"), FALSE, FALSE, 32, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_province"), createString("varchar"), FALSE, FALSE, 32, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_city"), createString("varchar"), FALSE, FALSE, 30, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_birthday"), createString("varchar"), FALSE, FALSE, 20, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("customer_description"), createString("varchar"), FALSE, FALSE, 88, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("create_time"), createString("datetime"), FALSE, FALSE, 8, 0);
    columnList->add(columnList, column);
    column = buildColumn(table, createString("update_time"), createString("datetime"), FALSE, FALSE, 8, 0);
    columnList->add(columnList, column);
    return columnList;
}

static List* initCustomerInfoNullableColumnList(Table *table) {
    List *nullableColumnList = createArrayList(8);
    return nullableColumnList;
}

static List* initCustomerInfoKeyColumnList(Table *table) {
    List *keyColumnList = createArrayList(2);
    Column *column = buildColumn(table, createString("customer_id"), createString("varchar"), FALSE, TRUE, 36, 0);
    keyColumnList->add(keyColumnList, column);
    return keyColumnList;
}

static List* initCustomerInfoKeyVarLenColumnList(Table *table) {
    List *keyVarLenColumnList = createArrayList(2);
    Column *column = buildColumn(table, createString("customer_id"), createString("varchar"), FALSE, TRUE, 36, 0);
    keyVarLenColumnList->add(keyVarLenColumnList, column);
    return keyVarLenColumnList;
}

static List* initCustomerInfoVariableLenColumnList(Table *table) {
    List *variableLenColumnList = createArrayList(8);
    Column *column = buildColumn(table, createString("customer_id"), createString("varchar"), FALSE, TRUE, 36, 0);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_name"), createString("varchar"), FALSE, TRUE, 32, 0);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_gender"), createString("varchar"), FALSE, TRUE, 20, 0);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_identifier"), createString("varchar"), FALSE, TRUE, 40, 0);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_job"), createString("varchar"), FALSE, TRUE, 20, 0);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_country"), createString("varchar"), FALSE, TRUE, 32, 0);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_province"), createString("varchar"), FALSE, TRUE, 32, 0);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_city"), createString("varchar"), FALSE, TRUE, 30, 0);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_birthday"), createString("varchar"), FALSE, TRUE, 20, 0);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("customer_description"), createString("varchar"), FALSE, TRUE, 88, 0);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("create_time"), createString("datetime"), FALSE, TRUE, 8, 0);
    variableLenColumnList->add(variableLenColumnList, column);
    column = buildColumn(table, createString("update_time"), createString("datetime"), FALSE, TRUE, 8, 0);
    variableLenColumnList->add(variableLenColumnList, column);
    return variableLenColumnList;
}