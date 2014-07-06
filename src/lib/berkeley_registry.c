#include "berkeley_registry.h"

void* berkely_registry_new(GError**);
void berkely_registry_free(void *self);
void berkely_registry_add(void *self, Info *info);

Registry BerkelyRegistryImpl =
{
    berkely_registry_new,
    berkely_registry_free,
    berkely_registry_add,
    NULL
};

Registry* BerkeleyRegistry()
{
    return &BerkelyRegistryImpl;
}

void* berkely_registry_new(GError **error)
{
    Registry *s = g_memdup(&BerkelyRegistryImpl, sizeof(Registry));

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

