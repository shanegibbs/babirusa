#include "info.h"
#include "files.h"

Info* bab_info_new(gchar *filename, int size, int mtime, Checksum *checksum)
{
    Info *info = g_slice_alloc(sizeof(Info));
    info->filename = g_strdup(filename);
    info->size = size;
    info->mtime = mtime;
    info->checksum = g_memdup(checksum, bab_digest_length());

    return info;
}

void bab_info_free(Info *info)
{
    g_free(info->filename);
    g_free(info->checksum);
    g_slice_free(Info, info);
}

void bab_info_log(Info *info)
{
    g_assert(info != NULL);
    g_assert(info->checksum != NULL);

    gchar *hex = bab_files_get_sha256_hex(info->checksum);
    g_debug("Info: filename=%s, size=%d, mtime=%d, checksum=%s", info->filename, info->size, info->mtime, hex);
    g_free(hex);
}
