typedef struct Object Object;

typedef struct Float Float;

struct Float {

	Object super;
	
	float value;

	float (*getValue)(Float *this);

    void (*setValue)(Float *this, float value);
};

Float *createFloat(float value);