typedef struct Object Object;

typedef struct Byte Byte;

struct Byte {

	Object super;
	
	byte value;

	byte (*getValue)(Byte *this);

    void (*setValue)(Byte *this, byte value);
};

Byte *createByte(byte value);