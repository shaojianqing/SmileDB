#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/type.h"

#include "objectType.h"
#include "byteType.h"

#define BYTE "Byte"

static byte getValue(Byte *this);

static void setValue(Byte *this, byte value);

static void bindFunction(Byte *this);

static int byteHashCode(Object *this);

static bool byteEquals(Object *this, Object *object);

static int byteCompare(Object *this, Object *object);

Byte *createByte(byte value) {
    Byte *number = (Byte*)malloc(sizeof(Byte));
    bindFunction(number);
    
    number->value = value;
    return number;
}

static void bindFunction(Byte *this) {
    if (this!=NULL) {
		Object *super = (Object *)this;
		super->name = BYTE;
		super->comparable = TRUE;
		super->equals = byteEquals;
		super->hashCode = byteHashCode;
		super->compare = byteCompare;

		this->getValue = getValue;
		this->setValue = setValue;	
	}
}

static byte getValue(Byte *this) {
    return this->value;
}

static void setValue(Byte *this, byte value) {
    this->value = value;
}

static int byteHashCode(Object *this) {
    Byte *number = (Byte *)this;
    return number->value;
}

static bool byteEquals(Object *this, Object *object) {
    if (this!=NULL && object!=NULL) {
		if (this==object) {
			return TRUE;		
		} else {
			Byte *number1 = (Byte *)this;
			Byte *number2 = (Byte *)object;
			return (number1->value == number2->value);
		}
	} else {
		return FALSE;	
	}
}

static int byteCompare(Object *this, Object *object) {
    Byte *number1 = (Byte *)this;
    Byte *number2 = (Byte *)object;

    return (number1->value - number2->value);
}