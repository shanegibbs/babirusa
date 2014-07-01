#include <stdio.h>
#include <glib.h>
#include <stdlib.h>

#include "info.h"
#include "backup.h"
#include "files.h"

#include <db.h>

void process_file(gchar* filename, struct stat *s);
void upload_file(Info *info);
void add_file(Info *info);

gboolean backup_to_path(gchar *from_path, gchar *backup_repo_path)
{
    g_debug("Starting backup from [%s] to repo at [%s]", from_path, backup_repo_path);

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
    add_file(info);

    bab_info_free(info);
}

void upload_file(Info *info)
{
}

void add_file(Info *info)
{
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



