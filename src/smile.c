#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "common/type.h"
#include "utils/utils.h"
#include "common/constants.h"
#include "data/objectType.h"
#include "data/byteType.h"
#include "data/stringType.h"
#include "data/doubleType.h"
#include "data/integerType.h"
#include "data/datetimeType.h"
#include "data/arrayList.h"
#include "data/hashMap.h"
#include "page/byteBuffer.h"
#include "page/header.h"
#include "table/table.h"
#include "table/definition.h"
#include "page/record.h"
#include "page/page.h"
#include "storage/storage.h"
#include "storage/index.h"

void resolveAndPrintOrderInfo();

void resolveAndPrintCustomerInfo();

int main(int argc, char **argv) {

    resolveAndPrintOrderInfo();
    resolveAndPrintCustomerInfo();
}

void resolveAndPrintOrderInfo() {

     File *corderInfoFile = fopen("data/order_info.ibd","rw");

    Table *table = initOrderInfoTableDefinition();

    List *primaryKeys = createArrayList(2);
    primaryKeys->add(primaryKeys, createString("98b05da5008d4a1fa248c49efac93471"));
    DataRecord *record = queryDataRecordByPrimaryKey(primaryKeys, table, corderInfoFile);
    if (record!=NULL) {
        String *orderId = (String *)record->getObject(record, createString("order_id"));
        String *productId = (String *)record->getObject(record, createString("product_id"));
        String *productName = (String *)record->getObject(record, createString("product_name"));
        //Double *unitPrice = (Double *)record->getObject(record, createString("unit_price"));
        String *currency = (String *)record->getObject(record, createString("currency"));
        Integer *quantity = (Integer *)record->getObject(record, createString("quantity"));
        //Double *serviceFee = (Double *)record->getObject(record, createString("service_fee"));
        String *consumerId = (String *)record->getObject(record, createString("consumer_id"));
        String *consumerName = (String *)record->getObject(record, createString("consumer_name"));
        String *merchantId = (String *)record->getObject(record, createString("merchant_id"));
        String *merchantName = (String *)record->getObject(record, createString("merchant_name"));
        String *orderDescription = (String *)record->getObject(record, createString("order_description"));
        Byte *isValid = (Byte *)record->getObject(record, createString("is_valid"));
        Datetime *gmtCreate = (Datetime *)record->getObject(record, createString("gmt_create"));
        Datetime *gmtModified = (Datetime *)record->getObject(record, createString("gmt_modified"));

        printf("QueryDataRecordByPrimaryKey orderId:            %s\n", orderId->value);
        printf("QueryDataRecordByPrimaryKey productId:          %s\n", productId->value);
        printf("QueryDataRecordByPrimaryKey productName:        %s\n", productName->value);
        //printf("QueryDataRecordByPrimaryKey unitPrice:          %f\n", unitPrice->value);
        printf("QueryDataRecordByPrimaryKey currency:           %s\n", currency->value);
        printf("QueryDataRecordByPrimaryKey quantity:           %d\n", quantity->value);
        //printf("QueryDataRecordByPrimaryKey serviceFee:         %s\n", serviceFee->value);
        printf("QueryDataRecordByPrimaryKey consumerId:         %s\n", consumerId->value);
        printf("QueryDataRecordByPrimaryKey consumerName:       %s\n", consumerName->value);
        printf("QueryDataRecordByPrimaryKey merchantId:         %s\n", merchantId->value);
        printf("QueryDataRecordByPrimaryKey merchantName:       %s\n", merchantName->value);
        if (orderDescription!=NULL) {
            printf("QueryDataRecordByPrimaryKey orderDescription:   %s\n", orderDescription->value);
        }
        printf("QueryDataRecordByPrimaryKey isValid:            %d\n", isValid->value);
        printf("QueryDataRecordByPrimaryKey gmtCreate:          %s\n", gmtCreate->toString(gmtCreate)->value);
        printf("QueryDataRecordByPrimaryKey gmtModified:        %s\n", gmtModified->toString(gmtModified)->value);
        printf("\n\n");
    } else {
        printf("QueryDataRecordByPrimaryKey Not Find Record!\n\n");
    }

    fclose(corderInfoFile);
}

void resolveAndPrintCustomerInfo() {

    File *customInfoFile = fopen("data/customer_info.ibd","rw");

    Table *table = initCustomerInfoTableDefinition();

    List *primaryKeys = createArrayList(2);
    primaryKeys->add(primaryKeys, createString("00aacd683acd4719b8b14db4d29c28dc"));
    DataRecord *record = queryDataRecordByPrimaryKey(primaryKeys, table, customInfoFile);
    if (record!=NULL) {
        String *customerId = (String *)record->getObject(record, createString("customer_id"));
        String *customerName = (String *)record->getObject(record, createString("customer_name"));
        String *customerGender = (String *)record->getObject(record, createString("customer_gender"));
        String *customerIdentifier = (String *)record->getObject(record, createString("customer_identifier"));
        String *customerJob = (String *)record->getObject(record, createString("customer_job"));
        String *customerCountry = (String *)record->getObject(record, createString("customer_country"));
        String *customerProvince = (String *)record->getObject(record, createString("customer_province"));
        String *customerCity = (String *)record->getObject(record, createString("customer_city"));
        String *customerBirthday = (String *)record->getObject(record, createString("customer_birthday"));
        Datetime *createTime = (Datetime *)record->getObject(record, createString("create_time"));
        Datetime *updateTime = (Datetime *)record->getObject(record, createString("update_time"));

        printf("QueryDataRecordByPrimaryKey customerId:         %s\n", customerId->value);
        printf("QueryDataRecordByPrimaryKey customerName:       %s\n", customerName->value);
        printf("QueryDataRecordByPrimaryKey customerGender:     %s\n", customerGender->value);
        printf("QueryDataRecordByPrimaryKey customerIdentifier: %s\n", customerIdentifier->value);
        printf("QueryDataRecordByPrimaryKey customerJob:        %s\n", customerJob->value);
        printf("QueryDataRecordByPrimaryKey customerCountry:    %s\n", customerCountry->value);
        printf("QueryDataRecordByPrimaryKey customerProvince:   %s\n", customerProvince->value);
        printf("QueryDataRecordByPrimaryKey customerCity:       %s\n", customerCity->value);
        printf("QueryDataRecordByPrimaryKey customerBirthday:   %s\n", customerBirthday->value);
        printf("QueryDataRecordByPrimaryKey createTime:         %s\n", createTime->toString(createTime)->value);
        printf("QueryDataRecordByPrimaryKey updateTime:         %s\n", updateTime->toString(updateTime)->value);
    } else {
        printf("QueryDataRecordByPrimaryKey Not Find Record!\n\n");
    }

    printf("Hello, Shaojianqing->SmileDB\n");

    fclose(customInfoFile);
}