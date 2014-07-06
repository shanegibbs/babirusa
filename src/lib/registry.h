#ifndef REGISTRY_H
#define REGISTRY_H

#include <glib.h>

#include "info.h"

typedef struct _RegistryInterface
{
    void* (*new)(void);
    void (*free)(void *self);
    void (*add)(void *self, Info *info);
    void *data;
} RegistryInterface;

#endif
