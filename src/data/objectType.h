typedef struct Object Object;

struct Object {

    char *name;

    bool comparable;

    int (*hashCode)(Object *this);

    bool (*equals)(Object *this, Object *object);

    int (*compare)(Object *this, Object *object);
};