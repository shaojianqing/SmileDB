typedef struct Object Object;

typedef struct Double Double;

struct Double {

	Object super;
	
	double value;

	double (*getValue)(Double *this);

    void (*setValue)(Double *this, double value);
};

Double *createDouble(double value);