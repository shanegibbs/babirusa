#include <stdio.h>
#include <glib.h>
#include <stdlib.h>

#include "info.h"
#include "backup.h"
#include "files.h"
#include "registry.h"

typedef struct _Data
{
    Registry *registry;
} Data;

// public functions
static void* new(GError**);
static void backup_engine_free(void *self);
static void set_registry(void *self, Registry*);
static gboolean backup_engine_backup_to_path(void *self, const gchar *from, gchar *to);

// private functions

BackupEngine DefaultBackupEngineImpl =
{
    new,
    backup_engine_free,
    set_registry,
    backup_engine_backup_to_path,
    NULL
};

static Data* get_data(BackupEngine *e)
{
    g_assert(e != NULL);
    g_assert(e->data != NULL);
    return e->data;
}

BackupEngine* DefaultBackupEngine()
{
  return &DefaultBackupEngineImpl;
}

static void* new(GError **error)
{
    g_debug("Creating new DefaultBackupEngine");

    BackupEngine *n = g_memdup(&DefaultBackupEngineImpl, sizeof(BackupEngine));
    n->data = g_malloc(sizeof(Data));
    return n;
}

static void backup_engine_free(void *self)
{
    g_free(get_data(self));
    g_free(self);
}

static void set_registry(void *self, Registry* reg)
{
    g_assert(self != NULL);
    g_assert(reg != NULL);

    Data *data = get_data(self);
    data->registry = reg;
}

static gboolean backup_engine_backup_to_path(void *self, const gchar *from, gchar *to)
{
    g_message("Starting backup from [%s] to repo at [%s]", from, to);

    Data *data = get_data(self);
    bab_file_scan(from, &process_file, (void*)data->registry);

    return TRUE;
}

void process_file(gchar* filename, struct stat *s, void *data)
{
    g_debug("Processing file %s", filename);

    GError *error = NULL;

    Checksum *chksum = bab_files_calc_file_hash(filename, &error);
    // chksum = (Checksum*) bab_files_get_sha256_hex(chksum);
    g_assert((chksum == NULL && error != NULL) || (chksum != NULL && error == NULL));
    if (error != NULL) {
        g_warning("Unable to process file %s: %s", filename, error->message);
        return;
    }

    g_assert(filename != NULL);
    g_assert(s != NULL);
    g_assert(chksum != NULL);
    Info *info = bab_info_new(filename, s->st_size, s->st_mtime, chksum);
    g_free(chksum);

    g_assert(info != NULL);
    bab_info_log("process_file", info);

    g_assert(data != NULL);
    Registry *reg = data;
    g_assert(reg->add != NULL);
    reg->add(reg, info);

    bab_info_free(info);
}
