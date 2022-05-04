typedef struct Object Object;

typedef struct Short Short;

struct Short {

	Object super;
	
	short value;

	short (*getValue)(Short *this);

    void (*setValue)(Short *this, short value);
};

Short *createShort(short value);