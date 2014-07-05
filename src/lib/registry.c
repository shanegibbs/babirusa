#include <stdio.h>
#include <db.h>

#include "registry.h"

typedef struct _BabRegistryPrivate BabRegistryPrivate;

struct _BabRegistryPrivate
{
    int hsize;
};

G_DEFINE_TYPE_WITH_PRIVATE(BabRegistry, bab_registry, G_TYPE_OBJECT)

static void
bab_registry_class_init(BabRegistryClass *klass)
{
}

static void
bab_registry_init(BabRegistry *self)
{
    BabRegistryPrivate *priv = bab_registry_get_instance_private(self);

    priv->hsize = 42;
    printf("%d", priv->hsize);
}
