#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/type.h"

#include "objectType.h"
#include "arrayList.h"

static u32 getSize(List *this);

static bool add(List *this, Object *object);

static Object* get(List *this, u32 index);

static bool removeByObject(List *this, Object *object);

static bool containsObject(List *this, Object *object);

static bool expandArrayList(List *this);

static bool addInner(List *this, Object *object);

List *createArrayList(u32 capacity) {
	if (capacity>0) {
		List *arrayList = (List *)malloc(sizeof(List));
		if (arrayList!=NULL) {
			arrayList->list = malloc(sizeof(Object *)*capacity);
			memset(arrayList->list, 0, sizeof(Object *)*capacity);
			arrayList->capacity = capacity;
			arrayList->size = 0;
			arrayList->add = add;
			arrayList->get = get;			
			arrayList->getSize = getSize;
			arrayList->remove = removeByObject;
			arrayList->containsObject = containsObject;
		}
		return arrayList;
	} else {
		return NULL;
	}
}

void destroyArrayList(List *this) {
	if (this!=NULL) {
		free(this->list);
		free(this);
	}
}

static u32 getSize(List *this) {
	if (this!=NULL) {
		return this->size;	
	} else {
		return 0;
	}
}

static bool add(List *this, Object *object) {
	if (this!=NULL && object!=NULL) {
		if (this->size>=this->capacity) {
			expandArrayList(this);
		}
		addInner(this, object);
		return TRUE;
	}
	return FALSE;
}

static Object* get(List *this, u32 index) {
	if (this!=NULL && index>=0 && index<this->size) {
		return this->list[index];	
	}
	return NULL;
}

static bool removeByObject(List *this, Object *object) {
	if (this!=NULL && object!=NULL) {
		int i=0, j=0;
		while (i<this->size) {
			Object *element = this->list[i];
			if (element->equals(element, object)) {
				break;
			}
			i++;		
		}
		j=i;
		while(j<this->size-1) {
			this->list[j]=this->list[j+1];
			j++;		
		}	
		this->list[this->size-1] = NULL;
		this->size--;
		return TRUE;
	}
	return FALSE;
}

static bool containsObject(List *this, Object *object) {
	if (this!=NULL && object!=NULL) {
		int i=0;
		while (i<this->size) {
			Object *element = this->list[i];
			if (element->equals(element, object)) {
				return TRUE;
			}
			++i;	
		}
	}
	return FALSE;
}

static bool addInner(List *this, Object *object) {
	u32 index = this->size;
	this->list[index] = object;
	this->size++;
	return TRUE;
}

static bool expandArrayList(List *this) {
	u32 newCapacity = this->capacity*2;
	Object **oldList = this->list;
	Object **newList = malloc(sizeof(Object *)*newCapacity);
	if (newList!=NULL) {
		memset(newList, 0, sizeof(Object *)*newCapacity);
		u32 i=0;
		for(i=0;i<this->size;++i) {
			newList[i] = oldList[i];		
		}	
		this->list = newList;
		this->capacity = newCapacity;
		free(oldList);
		return TRUE;
	}
	return FALSE;
}


