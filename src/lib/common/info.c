#include <string.h>

#include "info.h"
#include "files.h"
#include "serialize.h"

Info* bab_info_new(gchar *filename, unsigned long size, long mtime, Checksum *checksum)
{
  Info *info = g_slice_alloc(sizeof(Info));
  info->filename = g_strdup(filename);
  info->size = size;
  info->mtime = mtime;
  info->checksum = g_memdup(checksum, bab_digest_length() + 1);
  info->checksum[bab_digest_length()] = 0;

  bab_info_log("New", info);

  return info;
}

void bab_info_free(Info *info)
{
  g_free(info->filename);
  g_free(info->checksum);
  g_slice_free(Info, info);
}

void bab_info_log(const char* msg, Info *info)
{
  g_assert(info != NULL);
  g_assert(info->checksum != NULL);

  gchar *hex = bab_files_get_sha256_hex(info->checksum);
  g_debug("%s: Info[filename=%s, size=%lu, mtime=%lu, checksum=%s]", msg, info->filename, info->size, info->mtime, hex);
  g_free(hex);
}

char* bab_info_marshall(Info *info)
{
  char* data = g_malloc(bab_info_max_size());
  char* cur = data;

  write_ulong(info->size, &cur);
  write_ulong(info->mtime, &cur);
  write_string(info->filename, &cur);
  write_string((char*)info->checksum, &cur);

  return data;
}

Info* bab_info_unmarshall(char *data)
{
  Info *info = g_slice_alloc(sizeof(Info));
  char* cur = data;

  info->size = read_ulong(&cur);
  info->mtime = read_ulong(&cur);
  info->filename = read_string(&cur);
  info->checksum = (Checksum*)read_string(&cur);

  return info;
}

long bab_info_max_size()
{
  return 4096;
}
