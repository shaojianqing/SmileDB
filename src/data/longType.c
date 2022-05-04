#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/type.h"

#include "objectType.h"
#include "longType.h"

#define LONG "Long"

static long getValue(Long *this);

static void setValue(Long *this, long value);

static void bindFunction(Long *this);

static int byteHashCode(Object *this);

static bool byteEquals(Object *this, Object *object);

static int byteCompare(Object *this, Object *object);

Long *createLong(long value) {
    Long *number = (Long*)malloc(sizeof(Long));
    bindFunction(number);
    
    number->value = value;
    return number;
}

static void bindFunction(Long *this) {
    if (this!=NULL) {
		Object *super = (Object *)this;
		super->name = LONG;
		super->comparable = TRUE;
		super->equals = byteEquals;
		super->hashCode = byteHashCode;
		super->compare = byteCompare;

		this->getValue = getValue;
		this->setValue = setValue;	
	}
}

static long getValue(Long *this) {
    return this->value;
}

static void setValue(Long *this, long value) {
    this->value = value;
}

static int byteHashCode(Object *this) {
    Long *number = (Long *)this;
    return number->value;
}

static bool byteEquals(Object *this, Object *object) {
    if (this!=NULL && object!=NULL) {
		if (this==object) {
			return TRUE;		
		} else {
			Long *number1 = (Long *)this;
			Long *number2 = (Long *)object;
			return (number1->value == number2->value);
		}
	} else {
		return FALSE;	
	}
}

static int byteCompare(Object *this, Object *object) {
    Long *number1 = (Long *)this;
    Long *number2 = (Long *)object;

    return (number1->value - number2->value);
}