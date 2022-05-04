#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/type.h"

#include "objectType.h"
#include "stringType.h"

#define STRING "String"

static void bindFunction(String *this);

static u32 getLength(String *this);

static char* getValue(String *this);

static String* subString(String *this, int start, int end);

static String* catString(String *this, String *string);

static int stringHashCode(Object *this);

static bool stringEqualFun(Object *this, Object *object);

static int stringCompare(Object *this, Object *object);

String *createString(char *value) {
	String *string = (String *)malloc(sizeof(String));
	u32 length = strlen(value);
	if (value!=NULL && length>0) {
		bindFunction(string);
		string->length = length;
		string->value = malloc(length*2+1);
		memcpy(string->value, value, length);
		string->value[length] = '\0';
	} else {
		string->length = 0;
		string->value = malloc(DEFALUT_STRING_SPACE);
		memset(string->value, 0, DEFALUT_STRING_SPACE);
	}
	return string;
}

String* createStringWithRange(char *value, int range) {
	String *string = (String *)malloc(sizeof(String));
	u32 length = range;
	if (value!=NULL && length>0) {
		bindFunction(string);
		string->length = length;
		string->value = malloc(length*2+1);
		memcpy(string->value, value, length);
		string->value[length] = '\0';
	} else {
		string->length = 0;
		string->value = malloc(DEFALUT_STRING_SPACE);
		memset(string->value, 0, DEFALUT_STRING_SPACE);
	}
	return string;
}

void destroyString(String *string) {
	if (string!=NULL) {

	}
}

static void bindFunction(String *this) {
	if (this!=NULL) {
		Object *super = (Object *)this;
		super->name = STRING;
		super->comparable = TRUE;
		super->equals = stringEqualFun;
		super->hashCode = stringHashCode;
		super->compare = stringCompare;

		this->getLength = getLength;
		this->getValue = getValue;
		this->subString = subString;
		this->catString = catString;	
	}
}

static u32 getLength(String *this) {
	if (this!=NULL) {
		return this->length;
	} else {
		return 0;	
	}
}

static char* getValue(String *this) {
	if (this!=NULL) {
		return this->value;
	} else {
		return NULL;	
	}
}

static String* subString(String *this, int start, int end) {
	if (this!=NULL) {
		if (start<=end && start>=0 && end<this->length) {
			String *string = (String *)malloc(sizeof(String));
			bindFunction(string);
			string->length = end-start;
			string->value = malloc(string->length*2+1);
			memcpy(string->value, this->value+start, string->length);
			string->value[string->length] = '\0';
			return string;
		}
	}
	return NULL;
}

static String* catString(String *this, String *string) {
	if (this!=NULL) {
		if (string!=NULL && string->length>0) {
			u32 totalLength = this->length + string->length;
			char *newValue = malloc(totalLength+1);
			memcpy(newValue, this->value, this->length);
			memcpy(newValue + this->length, string->value, string->length);
			newValue[totalLength] = '\0';
			String *newString = createString(newValue);
			return newString;
		}	
	}
	return this;
}

static int stringHashCode(Object *this) {
	String *string = (String *)this;
	char *value = string->value;
	if (value!=NULL && *value!='\0') {
		int hashCode = 0;
		while (*value!='\0') {
			hashCode = hashCode*31 + (*value);
			value++;
		}	
		return hashCode;
	} else {
		return 0;	
	}
}

static bool stringEqualFun(Object *this, Object *object) {
	if (this!=NULL && object!=NULL) {
		if (this==object) {
			return TRUE;		
		} else {
			String *string1 = (String *)this;
			String *string2 = (String *)object;
			char *str1 = string1->value;
			char *str2 = string2->value;
			return (strcmp(str1, str2)==0);
		}
	} else {
		return FALSE;	
	}
}

static int stringCompare(Object *this, Object *object) {
	if (this!=NULL && object!=NULL) {
		if (this==object) {
			return 0;		
		} else {
			String *string1 = (String *)this;
			String *string2 = (String *)object;
			return strcmp(string1->value, string2->value);
		}
	} else {
		printf("stringCompare nullpointer exception!");
		exit(1);	
	}
}
