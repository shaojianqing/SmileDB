typedef struct Object Object;

typedef struct Datetime Datetime;

struct Datetime {

	Object super;

	u16 year;

	u16 month;

	u16 day;

	u16 hour;

	u16 minute;

	u16 second;

	u16 millisecond;

	u16 (*getYear)(Datetime *this);

	void (*setYear)(Datetime *this, u16 year);

	u16 (*getMonth)(Datetime *this);

	void (*setMonth)(Datetime *this, u16 month);

	u16 (*getDay)(Datetime *this);

	void (*setDay)(Datetime *this, u16 day);

	u16 (*getHour)(Datetime *this);

	void (*setHour)(Datetime *this, u16 hour);

	u16 (*getMinute)(Datetime *this);

	void (*setMinute)(Datetime *this, u16 minute);

	u16 (*getSecond)(Datetime *this);

	void (*setSecond)(Datetime *this, u16 second);

	u16 (*getMillisecond)(Datetime *this);

	void (*setMillisecond)(Datetime *this, u16 millisecond);

	String* (*toString)(Datetime *this);
};

Datetime* createWithDate(u16 year, u16 month, u16 day);

Datetime* createWithDatetime(u16 year, u16 month, u16 day, u16 hour, u16 minute, u16 second);

Datetime* createWithMilisecond(u16 year, u16 month, u16 day, u16 hour, u16 minute, u16 second, u16 millisecond);

void releaseDatetime(Datetime *datetime);
