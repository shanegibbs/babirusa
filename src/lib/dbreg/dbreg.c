#include <db.h>
#include <string.h>

#include "registry.h"

#include "dbreg.h"

static void* berkely_registry_new(GError**);
static void berkely_registry_free(void *self);
static void berkely_registry_add(void *self, Info *info);
static Info* berkely_registry_get(void *self, const char* filename);

static void list_db(DB *dbp);

static Registry BerkelyRegistryImpl = {
  berkely_registry_new,
  berkely_registry_free,
  berkely_registry_add,
  berkely_registry_get,
  NULL
};

typedef struct _Data {
  DB *db;
} Data;

static Data* get_data(void *self)
{
  g_assert(self != NULL);
  Registry *reg = self;
  return reg->data;
}

static DB* get_db(void *self)
{
  g_assert(self != NULL);
  Data *data = get_data(self);
  g_assert(data != NULL);
  g_assert(data->db != NULL);
  return data->db;
}

Registry* BerkeleyRegistry()
{
  return &BerkelyRegistryImpl;
}

static void* berkely_registry_new(GError **error)
{
  Registry *s = g_memdup(&BerkelyRegistryImpl, sizeof(Registry));

  const gchar* db_filename = "my_db.db";

  g_debug("Opening DB %s", db_filename);
  DB *dbp;
  int ret;

  ret = db_create(&dbp, NULL, 0);
  if (ret != 0) {
    g_error("failed to create db");
  }

  ret = dbp->open(dbp, NULL, db_filename, NULL, DB_BTREE, DB_CREATE, 0);
  if (ret != 0) {
    g_error("failed to open db");
  }

  s->data = g_malloc(sizeof(Data));
  get_data(s)->db = dbp;

  g_assert(get_db(s) != NULL);
  return s;
}

static void berkely_registry_free(void *self)
{
  g_debug("Shutting down berkeley DB");
  DB *dbp = get_db(self);
  if (dbp != NULL) {
    list_db(dbp);
    dbp->close(dbp, 0);
  }
}

static void list_db(DB *dbp)
{
  g_message("Listing database");

  DBC *cursorp;
  dbp->cursor(dbp, NULL, &cursorp, 0);

  DBT key, data;
  memset(&key, 0, sizeof(DBT));
  memset(&data, 0, sizeof(DBT));

  int ret;
  while ((ret = cursorp->get(cursorp, &key, &data, DB_NEXT)) == 0) {
    g_debug("Listing: key.size=%i, strlen(key.data)=%i", key.size, (int)strlen(key.data));
    g_assert(strlen(key.data) + 1 == key.size);
    g_message("Key=%s", (char*)key.data);

    Info *info = bab_info_unmarshall(key.data);
    bab_info_log("Unmarshalled", info);

  }
  if (ret != DB_NOTFOUND) {
    g_error("Got DB error");
  }

  if (cursorp != NULL) {
    cursorp->close(cursorp);
  }
}

static void berkely_registry_add(void *self, Info *info)
{
  g_assert(self != NULL);
  g_assert(info != NULL);

  g_debug("Berkeley registry adding %s", info->filename);

  DB *dbp = NULL;
  int ret;

  dbp = get_db(self);
  g_assert(dbp != NULL);

  DBT key, data;
  memset(&key, 0, sizeof(key));
  memset(&data, 0, sizeof(data));

  bab_info_log("Persisting", info);

  char* info_data = bab_info_marshall(info);

  key.data = info->filename;
  key.size = strlen(info->filename) + 1;
  key.flags = DB_DBT_USERMEM;

  data.data = info_data;
  data.size = *info_data;

  if ((ret = dbp->put(dbp, NULL, &key, &data, 0)) == 0) {
    g_debug("db: '%s' key stored", (char*)key.data);
  } else {
    dbp->err(dbp, ret, "DB->put");
    g_warning("DB put failed");
  }


}

static Info* berkely_registry_get(void *self, const char* filename)
{
  DB *dbp = NULL;
  int ret;

  dbp = get_db(self);
  g_assert(dbp != NULL);

  DBT key, data;
  memset(&key, 0, sizeof(key));
  memset(&data, 0, sizeof(data));

  key.data = (void*) filename;
  key.size = strlen(filename) + 1;
  key.flags = DB_DBT_USERMEM;

  if ((ret = dbp->get(dbp, NULL, &key, &data, 0)) == 0) {
    g_debug("db: '%s' key retreived", (char*)key.data);
  } else {
    dbp->err(dbp, ret, "DB->get");
    g_warning("DB get failed");
  }

  return bab_info_unmarshall(data.data);
}
