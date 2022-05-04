#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "common/type.h"
#include "utils/utils.h"
#include "common/constants.h"
#include "data/objectType.h"
#include "data/stringType.h"
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

int main(int argc, char **argv) {

    File *customInfoFile = fopen("data/customer_info.ibd","rw");

    Table *table = initCustomerInfoTableDefinition();

    List *primaryKeys = createArrayList(2);
    primaryKeys->add(primaryKeys, createString("0089dea66ae84835bad1170b3ef4746b"));
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

        printf("QueryDataRecordByPrimaryKey customerId:         %s\n", customerId->value);
        printf("QueryDataRecordByPrimaryKey customerName:       %s\n", customerName->value);
        printf("QueryDataRecordByPrimaryKey customerGender:     %s\n", customerGender->value);
        printf("QueryDataRecordByPrimaryKey customerIdentifier: %s\n", customerIdentifier->value);
        printf("QueryDataRecordByPrimaryKey customerJob:        %s\n", customerJob->value);
        printf("QueryDataRecordByPrimaryKey customerCountry:    %s\n", customerCountry->value);
        printf("QueryDataRecordByPrimaryKey customerProvince:   %s\n", customerProvince->value);
        printf("QueryDataRecordByPrimaryKey customerCity:       %s\n", customerCity->value);
        printf("QueryDataRecordByPrimaryKey customerBirthday:   %s\n", customerBirthday->value);
    } else {
        printf("QueryDataRecordByPrimaryKey Not Find Record!\n\n");
    }

    printf("Hello, Shaojianqing->SmileDB\n");

    fclose(customInfoFile);
}