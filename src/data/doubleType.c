#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/type.h"

#include "objectType.h"
#include "doubleType.h"

#define DOUBLE "Double"

static double getValue(Double *this);

static void setValue(Double *this, double value);

static void bindFunction(Double *this);

static int doubleHashCode(Object *this);

static bool doubleEquals(Object *this, Object *object);

static int doubleCompare(Object *this, Object *object);

Double *createDouble(double value) {
    Double *number = (Double*)malloc(sizeof(Double));
    bindFunction(number);
    
    number->value = value;
    return number;
}

static void bindFunction(Double *this) {
    if (this!=NULL) {
		Object *super = (Object *)this;
		super->name = DOUBLE;
		super->comparable = TRUE;
		super->equals = doubleEquals;
		super->hashCode = doubleHashCode;
		super->compare = doubleCompare;

		this->getValue = getValue;
		this->setValue = setValue;	
	}
}

static double getValue(Double *this) {
    return this->value;
}

static void setValue(Double *this, double value) {
    this->value = value;
}

static int doubleHashCode(Object *this) {
    Double *number = (Double *)this;
    return number->value;
}

static bool doubleEquals(Object *this, Object *object) {
    if (this!=NULL && object!=NULL) {
		if (this==object) {
			return TRUE;		
		} else {
			Double *number1 = (Double *)this;
			Double *number2 = (Double *)object;
			return (number1->value == number2->value);
		}
	} else {
		return FALSE;	
	}
}

static int doubleCompare(Object *this, Object *object) {
    Double *number1 = (Double *)this;
    Double *number2 = (Double *)object;

    return (number1->value - number2->value);
}