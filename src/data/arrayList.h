
typedef struct List List;

struct List {
	
	Object **list;

	u32 capacity;

	u32 size;

	u32 (*getSize)(List *this);

	bool (*add)(List *this, Object *object);

	Object* (*get)(List *this, u32 index);

	bool (*remove)(List *this, Object *object);
	
	bool (*containsObject)(List *this, Object *object);
};

List *createArrayList(u32 capacity);

void destroyArrayList(List *this);

