typedef struct Object Object;

typedef struct Integer Integer;

struct Integer {

	Object super;
	
	int value;

	int (*getValue)(Integer *this);

    void (*setValue)(Integer *this, int value);
};

Integer *createInteger(int value);