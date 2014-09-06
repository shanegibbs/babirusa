#include <string.h>

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

char* bab_info_marshall(Info *info)
{
  int filename_size = strlen(info->filename);
  int checksum_size = bab_digest_length();
  int size = 4 + filename_size + checksum_size;

  char* data = g_malloc(size);
  data[0] = size;
  data[1] = info->size;
  data[2] = info->mtime;
  data[3] = filename_size;
  memcpy(data + 4, info->filename, filename_size);
  memcpy(data + 4 + filename_size, info->checksum, checksum_size);
  return data;
}

Info* bab_info_unmarshall(char *data)
{
  Info *info = g_slice_alloc(sizeof(Info));

  int idx = 1;
  info->size = data[idx++];
  info->mtime = data[idx++];
  int filename_size = data[idx++];
  int checksum_size = bab_digest_length();

  info->filename = g_malloc(filename_size + 1);
  memcpy(info->filename, data + idx, filename_size);
  info->filename[filename_size] = 0;

  info->checksum = g_malloc(checksum_size + 1);
  memcpy(info->checksum, data + idx + filename_size, checksum_size);
  info->checksum[checksum_size] = 0;

  return info;
}
