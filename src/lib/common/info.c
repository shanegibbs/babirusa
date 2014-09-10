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

char ulong_char(unsigned long i, short pos)
{
  short moves = (3 - pos) * 8;
  return i >> moves;
}

char ulong_char1(unsigned long i)
{
  return i & 0xffffffff;
}

unsigned long char_ulong0(char i)
{
  return (long)i << 32;
}

unsigned long char_ulong1(char i)
{
  return i & 0xffffffff;
}

char* bab_info_marshall(Info *info)
{
  char* data = g_malloc(1024);
  char* cur = data;

  write_ulong(info->size, &cur);
  write_ulong(info->mtime, &cur);
  write_string(info->filename, &cur);
  write_string((char*)info->checksum, &cur);

  // int filename_len = strlen(info->filename);
  // write_ulong(filename_len, &cur);
  // memcpy(cur, info->filename, filename_len);

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

char* bab_info_marshall2(Info *info)
{
  int filename_size = strlen(info->filename);
  int checksum_size = bab_digest_length();
  int size = 6 + filename_size + checksum_size;

  char* data = g_malloc(size);

  int idx = 0;
  data[idx++] = size;
  data[idx++] = ulong_char(info->size, 0);
  data[idx++] = ulong_char(info->size, 1);
  data[idx++] = info->mtime >> 32;
  data[idx++] = info->mtime & 0xffffffff;
  data[idx++] = filename_size;
  memcpy(data + idx, info->filename, filename_size);
  memcpy(data + idx + filename_size, info->checksum, checksum_size);
  g_assert_cmpint(idx + filename_size + checksum_size, ==, size);
  printf("marshall size %x %x - %lu\n", data[1], data[2], info->size);
  return data;
}

Info* bab_info_unmarshall2(char *data)
{
  Info *info = g_slice_alloc(sizeof(Info));

  int idx = 1;
  printf("unmarshall size %x %x\n", data[1], data[2]);
  info->size = (long)data[idx++] << 32;
  info->size += data[idx++];
  info->mtime = (long)data[idx++] << 32;
  info->mtime += data[idx++];
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
