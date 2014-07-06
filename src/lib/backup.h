#include <glib.h>

#include "registry.h"

typedef struct _BackupEngine
{
    void* (*new)(GError**);
    void (*free)(void *self);
    void (*set_registry)(void *self, Registry*);
    gboolean (*backup_to_path)(void *self, const gchar *from, gchar *to);
    void *data;
} BackupEngine;

BackupEngine* DefaultBackupEngine();

gboolean backup_to_path(const gchar *from_path, gchar *backup_repo_path, Registry*);
