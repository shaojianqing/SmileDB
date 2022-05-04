#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/type.h"

#include "objectType.h"
#include "integerType.h"

#define INTEGER "Integer"

static int getValue(Integer *this);

static void setValue(Integer *this, int value);

static void bindFunction(Integer *this);

static int integerHashCode(Object *this);

static bool integerEquals(Object *this, Object *object);

static int integerCompare(Object *this, Object *object);

Integer *createInteger(int value) {
    Integer *number = (Integer*)malloc(sizeof(Integer));
    bindFunction(number);
    
    number->value = value;
    return number;
}

static void bindFunction(Integer *this) {
    if (this!=NULL) {
		Object *super = (Object *)this;
		super->name = INTEGER;
		super->comparable = TRUE;
		super->equals = integerEquals;
		super->hashCode = integerHashCode;
		super->compare = integerCompare;

		this->getValue = getValue;
		this->setValue = setValue;	
	}
}

static int getValue(Integer *this) {
    return this->value;
}

static void setValue(Integer *this, int value) {
    this->value = value;
}

static int integerHashCode(Object *this) {
    Integer *number = (Integer *)this;
    return number->value;
}

static bool integerEquals(Object *this, Object *object) {
    if (this!=NULL && object!=NULL) {
		if (this==object) {
			return TRUE;		
		} else {
			Integer *number1 = (Integer *)this;
			Integer *number2 = (Integer *)object;
			return (number1->value == number2->value);
		}
	} else {
		return FALSE;	
	}
}

static int integerCompare(Object *this, Object *object) {
    Integer *number1 = (Integer *)this;
    Integer *number2 = (Integer *)object;

    return (number1->value - number2->value);
}