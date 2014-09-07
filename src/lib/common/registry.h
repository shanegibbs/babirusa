#ifndef REGISTRY_H
#define REGISTRY_H

#include <glib.h>

#include "info.h"

typedef struct Registry
{
    void* (*new)(GError**);
    void (*free)(void *self);
    void (*add)(void *self, Info *info);
    Info* (*get)(void *self, const char* filename);
    void *data;
} Registry;

#endif
