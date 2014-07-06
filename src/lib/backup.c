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
void* backup_engine_new(GError**);
void backup_engine_free(void *self);
void backup_engine_set_registry(void *self, Registry*);
gboolean backup_engine_backup_to_path(void *self, const gchar *from, gchar *to);

// private functions
void process_file(gchar* filename, struct stat *s, void*);

BackupEngine DefaultBackupEngineImpl =
{
    backup_engine_new,
    backup_engine_free,
    backup_engine_set_registry,
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

void* backup_engine_new(GError **error)
{
    g_debug("Creating new DefaultBackupEngine");

    BackupEngine *n = g_memdup(&DefaultBackupEngineImpl, sizeof(BackupEngine));
    n->data = g_malloc(sizeof(Data));
    return n;
}

void backup_engine_free(void *self)
{
    g_free(get_data(self));
    g_free(self);
}

void backup_engine_set_registry(void *self, Registry* reg)
{
    g_assert(self != NULL);
    g_assert(reg != NULL);

    Data *data = get_data(self);
    data->registry = reg;
}

gboolean backup_engine_backup_to_path(void *self, const gchar *from, gchar *to)
{
    g_message("Starting backup from [%s] to repo at [%s]", from, to);

    Data *data = get_data(self);
    bab_file_scan(from, &process_file, data->registry);

    return TRUE;
}

void process_file(gchar* filename, struct stat *s, void *r)
{
    g_debug("Processing file %s", filename);

    GError *error = NULL;

    Checksum *chksum = bab_files_calc_file_hash(filename, &error);
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
    bab_info_log(info);

    Registry *reg = r;
    reg->add(reg, info);

    bab_info_free(info);
}
