#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/type.h"

#include "objectType.h"
#include "floatType.h"

#define FLOAT "Float"

static float getValue(Float *this);

static void setValue(Float *this, float value);

static void bindFunction(Float *this);

static int floatHashCode(Object *this);

static bool floatEquals(Object *this, Object *object);

static int floatCompare(Object *this, Object *object);

Float *createFloat(float value) {
    Float *number = (Float*)malloc(sizeof(Float));
    bindFunction(number);
    
    number->value = value;
    return number;
}

static void bindFunction(Float *this) {
    if (this!=NULL) {
		Object *super = (Object *)this;
		super->name = FLOAT;
		super->comparable = TRUE;
		super->equals = floatEquals;
		super->hashCode = floatHashCode;
		super->compare = floatCompare;

		this->getValue = getValue;
		this->setValue = setValue;	
	}
}

static float getValue(Float *this) {
    return this->value;
}

static void setValue(Float *this, float value) {
    this->value = value;
}

static int floatHashCode(Object *this) {
    Float *number = (Float *)this;
    return number->value;
}

static bool floatEquals(Object *this, Object *object) {
    if (this!=NULL && object!=NULL) {
		if (this==object) {
			return TRUE;		
		} else {
			Float *number1 = (Float *)this;
			Float *number2 = (Float *)object;
			return (number1->value == number2->value);
		}
	} else {
		return FALSE;	
	}
}

static int floatCompare(Object *this, Object *object) {
    Float *number1 = (Float *)this;
    Float *number2 = (Float *)object;

    return (number1->value - number2->value);
}