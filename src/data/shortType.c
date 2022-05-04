#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/type.h"

#include "objectType.h"
#include "shortType.h"

#define SHORT "Short"

static short getValue(Short *this);

static void setValue(Short *this, short value);

static void bindFunction(Short *this);

static int shortHashCode(Object *this);

static bool shortEquals(Object *this, Object *object);

static int shortCompare(Object *this, Object *object);

Short *createShort(short value) {
    Short *number = (Short*)malloc(sizeof(Short));
    bindFunction(number);
    
    number->value = value;
    return number;
}

static void bindFunction(Short *this) {
    if (this!=NULL) {
		Object *super = (Object *)this;
		super->name = SHORT;
		super->comparable = TRUE;
		super->equals = shortEquals;
		super->hashCode = shortHashCode;
		super->compare = shortCompare;

		this->getValue = getValue;
		this->setValue = setValue;	
	}
}

static short getValue(Short *this) {
    return this->value;
}

static void setValue(Short *this, short value) {
    this->value = value;
}

static int shortHashCode(Object *this) {
    Short *number = (Short *)this;
    return number->value;
}

static bool shortEquals(Object *this, Object *object) {
    if (this!=NULL && object!=NULL) {
		if (this==object) {
			return TRUE;		
		} else {
			Short *number1 = (Short *)this;
			Short *number2 = (Short *)object;
			return (number1->value == number2->value);
		}
	} else {
		return FALSE;	
	}
}

static int shortCompare(Object *this, Object *object) {
    Short *number1 = (Short *)this;
    Short *number2 = (Short *)object;

    return (number1->value - number2->value);
}