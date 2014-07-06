#include <stdio.h>
#include <glib.h>
#include <stdlib.h>

#include "info.h"
#include "backup.h"
#include "files.h"
#include "registry.h"

void process_file(gchar* filename, struct stat *s);
void upload_file(Info *info);
void add_file(Info *info);

RegistryInterface *reg;

gboolean backup_to_path(const gchar *from_path, gchar *backup_repo_path, RegistryInterface *registry)
{
    g_debug("Starting backup from [%s] to repo at [%s]", from_path, backup_repo_path);
    reg = registry;

    bab_file_scan(from_path, &process_file);

    // for each source file
    // - create hash
    // - add file to index
    // - add file to data path

    return TRUE;
}

void process_file(gchar* filename, struct stat *s)
{
    g_debug("Processing file %s", filename);

    Checksum *chksum = bab_files_calc_file_hash(filename);
    Info *info = bab_info_new(filename, s->st_size, s->st_mtime, chksum);
    g_free(chksum);

    bab_info_log(info);

    // do stuff with info...

    upload_file(info);
    reg->add(reg, info);

    bab_info_free(info);
}

void upload_file(Info *info)
{
}
