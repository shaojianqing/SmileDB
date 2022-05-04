typedef struct Object Object;

typedef struct Long Long;

struct Long {

	Object super;
	
	long value;

	long (*getValue)(Long *this);

    void (*setValue)(Long *this, long value);
};

Long *createLong(long value);