#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include "../common/constants.h"
#include "../common/type.h"

#include "objectType.h"
#include "stringType.h"
#include "datetimeType.h"

#define DATETIME "Datetime"

#define DATETIME_FORMAT_SIZE 64

#define FORMAT_WITH_MILISECOND "%04d-%02d-%02d %02d:%02d:%02d %06d"
#define FORMAT_WITHOUT_MILISECOND "%04d-%02d-%02d %02d:%02d:%02d"

static u16 getYear(Datetime *this);

static void setYear(Datetime *this, u16 year);

static u16 getMonth(Datetime *this);

static void setMonth(Datetime *this, u16 month);

static u16 getDay(Datetime *this);

static void setDay(Datetime *this, u16 day);

static u16 getHour(Datetime *this);

static void setHour(Datetime *this, u16 hour);

static u16 getMinute(Datetime *this);

static void setMinute(Datetime *this, u16 minute);

static u16 getSecond(Datetime *this);

static void setSecond(Datetime *this, u16 second);

static u16 getMillisecond(Datetime *this);

static void setMillisecond(Datetime *this, u16 millisecond);

static String* toString(Datetime *this);

static void bindFunction(Datetime *this);

Datetime* createWithDate(u16 year, u16 month, u16 day) {
	Datetime *datetime = (Datetime*)malloc(sizeof(Datetime));
	if (datetime!=NULL) {
		bindFunction(datetime);

		datetime->year = year;
		datetime->month = month;
		datetime->day = day;
		datetime->hour = 0;
		datetime->minute = 0;
		datetime->second = 0;
		datetime->millisecond = 0;
	}
	return datetime;
}

Datetime* createWithDatetime(u16 year, u16 month, u16 day, u16 hour, u16 minute, u16 second) {
	Datetime *datetime = (Datetime*)malloc(sizeof(Datetime));
	if (datetime!=NULL) {
		bindFunction(datetime);

		datetime->year = year;
		datetime->month = month;
		datetime->day = day;
		datetime->hour = hour;
		datetime->minute = minute;
		datetime->second = second;
		datetime->millisecond = 0;
	}
	return datetime;
}

Datetime* createWithMilisecond(u16 year, u16 month, u16 day, u16 hour, u16 minute, u16 second, u16 millisecond) {
	Datetime *datetime = (Datetime*)malloc(sizeof(Datetime));
	if (datetime!=NULL) {
		bindFunction(datetime);

		datetime->year = year;
		datetime->month = month;
		datetime->day = day;
		datetime->hour = hour;
		datetime->minute = minute;
		datetime->second = second;
		datetime->millisecond = millisecond;
	}
	return datetime;
}

static void bindFunction(Datetime *this) {
	this->getYear = getYear;
	this->setYear = setYear;
	this->getMonth = getMonth;
	this->setMonth = setMonth;
	this->getDay = getDay;
	this->setDay = setDay;
	this->getHour = getHour;
	this->setHour = setHour;
	this->getMinute = getMinute;
	this->setMinute = setMinute;
	this->getSecond = getSecond;
	this->setSecond = setSecond;
	this->getMillisecond = getMillisecond;
	this->setMillisecond = setMillisecond;
	this->toString = toString;
}

static u16 getYear(Datetime *this) {
	return this->year;
}

static void setYear(Datetime *this, u16 year) {
	this->year = year;
}

static u16 getMonth(Datetime *this) {
	return this->month;
}

static void setMonth(Datetime *this, u16 month) {
	this->month = month;
}

static u16 getDay(Datetime *this) {
	return this->day;
}

static void setDay(Datetime *this, u16 day) {
	this->day = day;
}

static u16 getHour(Datetime *this) {
	return this->hour;
}

static void setHour(Datetime *this, u16 hour) {
	this->hour = hour;
}

static u16 getMinute(Datetime *this) {
	return this->minute;
}

static void setMinute(Datetime *this, u16 minute) {
	this->minute = minute;
}

static u16 getSecond(Datetime *this) {
	return this->second;
}

static void setSecond(Datetime *this, u16 second) {
	this->second = second;
}

static u16 getMillisecond(Datetime *this) {
	return this->millisecond;
}

static void setMillisecond(Datetime *this, u16 millisecond) {
	this->millisecond = millisecond;
}

static String* toString(Datetime *this) {
	char datetimeBuf[DATETIME_FORMAT_SIZE];
	u8 i=0;
	for (i=0;i<DATETIME_FORMAT_SIZE;++i) {
		datetimeBuf[i] = '\0';
	}
	if (this->millisecond>0) {
		sprintf(datetimeBuf, FORMAT_WITH_MILISECOND, this->year, this->month, this->day, 
			this->hour, this->minute, this->second, this->millisecond);
	} else {
		sprintf(datetimeBuf, FORMAT_WITHOUT_MILISECOND, this->year, this->month, this->day, 
			this->hour, this->minute, this->second);
	}
	return createString(datetimeBuf);
}

void releaseDatetime(Datetime *datetime) {
	if (datetime!=NULL) {
		free(datetime);
	}
}