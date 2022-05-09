#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/type.h"
#include "../data/objectType.h"
#include "../data/stringType.h"
#include "../data/arrayList.h"
#include "../data/hashMap.h"

#include "table.h"

#define COLUMN "Column"

static void bindFunction(Column *this);

static bool isFixedLength(Column *column);

static bool isVariableLength(Column *column);

static bool columnEquals(Type *obj1, Type *obj2);

Column *buildColumn(Table *table, String *name, String *type, bool nullable, bool isPrimaryKey, u16 length, u16 precision) {
    Column *column = (Column*)malloc(sizeof(Column));

    bindFunction(column);

    column->table = table;
    column->name = name;
    column->type = type;
    column->nullable = nullable;
    column->isPrimaryKey = isPrimaryKey;
    column->length = length;
    column->precision = precision;

    return column;
}

static void bindFunction(Column *this) {

    Object *super = (Object *)this;
    super->name = COLUMN;
    super->compare = NULL;
    super->hashCode = NULL;
    super->equals = columnEquals;
    super->comparable = FALSE;

    this->isVariableLength = isVariableLength;
    this->isFixedLength = isFixedLength;
}

static bool isVariableLength(Column *column) {
    if (strcmp(column->type->value, TYPE_VARCHAR)==0 || 
        strcmp(column->type->value, TYPE_VARBINARY)==0 || 
        strcmp(column->type->value, TYPE_TINYBLOB)==0 || 
        strcmp(column->type->value, TYPE_BLOB)==0 || 
        strcmp(column->type->value, TYPE_MEDIUMBLOB)==0 || 
        strcmp(column->type->value, TYPE_LONGBLOB)==0 || 
        strcmp(column->type->value, TYPE_TINYTEXT)==0 || 
        strcmp(column->type->value, TYPE_TEXT)==0 || 
        strcmp(column->type->value, TYPE_MEDIUMTEXT)==0 || 
        strcmp(column->type->value, TYPE_LONGTEXT)==0) {
            return TRUE;
    } else {
        return FALSE;
    }
}

static bool isFixedLength(Column *column) {
    if (strcmp(column->type->value, TYPE_CHAR)==0 || 
        strcmp(column->type->value, TYPE_BINARY)==0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static bool columnEquals(Type *obj1, Type *obj2) {
	if (obj1!=NULL && obj2!=NULL) {
		if (obj1==obj2) {
			return TRUE;		
		} else {
			Column *column1 = (Column *)obj1;
			Column *column2 = (Column *)obj2;
			if (column1->name!=NULL && column2->name!=NULL) {
                Object *coumnName1 = column1->name;
                Object *coumnName2 = column2->name;

                return coumnName1->equals(coumnName1, coumnName2);
			} else if (column1->name==NULL && column2->name==NULL) {
				return TRUE;
			}
			return FALSE;
		}
	} else if (obj1==NULL && obj2==NULL) {
		return TRUE;
	} else {
		return FALSE;	
	}
}