#ifndef BERKELEY_REGISTRY_H
#define BERKELEY_REGISTRY_H

#include <glib.h>

#include "registry.h"

void* berkely_registry_new();
void berkely_registry_free(void *self);
void berkely_registry_add(void *self, Info *info);

RegistryInterface _BerkelyRegistryImpl =
{
    berkely_registry_new,
    berkely_registry_free,
    berkely_registry_add,
    NULL
};

RegistryInterface *Berkeley = &_BerkelyRegistryImpl;

void* berkely_registry_new()
{
    RegistryInterface *s = g_memdup(Berkeley, sizeof(RegistryInterface));

    s->data = NULL;
    return s;
}

void berkely_registry_free(void *self)
{
}

void berkely_registry_add(void *self, Info *info)
{
    g_message("Berkeley registry add");
}

#endif
