#include <glib.h>

struct Class
{
    size_t size;
    void * (* ctor) (void * self);
    void * (* dtor) (void * self);
};

size_t sizeOf (const void * self)
{
    const struct Class * const * cp = self;
    g_assert(self && *cp);
    return (*cp)->size;
}

void* new(const void *_class)
{
    const struct Class *class = _class;
    void *p = g_malloc(class->size);
    *(const struct Class**)p = class;
    if (class->ctor)
    {
        p = class->ctor(p);
    }
    return p;
}

void delete (void *self)
{
    const struct Class **cp = self;
    if (self && *cp && (*cp)->dtor)
        self = (*cp)->dtor(self);
    free(self);
}

