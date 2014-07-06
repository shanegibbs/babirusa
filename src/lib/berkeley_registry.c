#include "berkeley_registry.h"

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

RegistryInterface* BerkeleyRegistry()
{
    return &_BerkelyRegistryImpl;
}

void* berkely_registry_new()
{
    RegistryInterface *s = g_memdup(&_BerkelyRegistryImpl, sizeof(RegistryInterface));

    s->data = NULL;
    return s;
}

void berkely_registry_free(void *self)
{
}

void berkely_registry_add(void *self, Info *info)
{
    g_message("Berkeley registry add %s", info->filename);

    DB *dbp;
    u_int32_t flags;
    int ret;

    ret = db_create(&dbp, NULL, 0);
    if (ret != 0)
    {
        g_error("failed to create db");
    }

    flags = DB_CREATE;
    ret = dbp->open(dbp, NULL, "my_db.db", NULL, DB_BTREE, flags, 0);
    if (ret != 0)
    {
        g_error("failed to open db");
    }


    dbp->close(dbp, 0);
}

