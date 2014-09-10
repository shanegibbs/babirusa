#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "info.h"
#include "serialize.h"

void print_hex_memory(void *mem, int count)
{
  int i;
  unsigned char *p = (unsigned char *)mem;
  for (i = 0; i < count; i++) {
    printf("0x%02x, ", p[i]);
    if (i % 16 == 15) {
      printf("\n");
    }
  }
  printf("\n");
}

void info_marshall_test(void)
{
  Checksum *checksum = (Checksum*) "ABCDEFGHIJKJMNOPQRSTUVWXYZ012345";

  unsigned long size = 1;
  long mtime = 300;

  Info *info = bab_info_new("file", size, mtime, checksum);

  g_assert_true(info->size == size);
  g_assert_cmpint(info->mtime, ==, mtime);
  g_assert_cmpstr(info->filename, ==, "file");
  g_assert_cmpstr((char*)info->checksum, ==, "ABCDEFGHIJKJMNOPQRSTUVWXYZ012345");

  char *data = bab_info_marshall(info);

  g_assert(data != NULL);
  int idx = 0;
  g_assert_cmpstr(to_hex_str(&data[idx++], 1), ==, "01");
  g_assert_cmpstr(to_hex_str(&data[idx++], 1), ==, "AC");
  g_assert_cmpstr(to_hex_str(&data[idx++], 1), ==, "02");
  g_assert_cmpstr(to_hex_str(&data[idx++], 1), ==, "04");
  g_assert_cmpint(data[idx++], ==, 'f');
  g_assert_cmpint(data[idx++], ==, 'i');
  g_assert_cmpint(data[idx++], ==, 'l');
  g_assert_cmpint(data[idx++], ==, 'e');
  g_assert_cmpstr(to_hex_str(&data[idx++], 1), ==, "20");
  g_assert_cmpint(data[idx++], ==, 'A');
  g_assert_cmpint(data[idx++], ==, 'B');
  g_assert_cmpint(data[idx++], ==, 'C');

  g_assert_true(info->size == size);
  g_assert_cmpint(info->mtime, ==, mtime);
  g_assert_cmpstr(info->filename, ==, "file");
  g_assert_cmpstr((char*)info->checksum, ==, "ABCDEFGHIJKJMNOPQRSTUVWXYZ012345");

  bab_info_free(info);
}

void info_marshall_roundtrip_test(void)
{
  Checksum *checksum = (Checksum*) "ABCDEFGHIJKJMNOPQRSTUVWXYZ012345";

  unsigned long size = 300;
  long mtime = 400;

  Info *info = bab_info_new("file", size, mtime, checksum);

  g_assert_true(info->size == size);
  g_assert_cmpint(info->mtime, ==, mtime);
  g_assert_cmpstr(info->filename, ==, "file");
  g_assert_cmpstr((char*)info->checksum, ==, "ABCDEFGHIJKJMNOPQRSTUVWXYZ012345");

  char *data = bab_info_marshall(info);

  Info *info2 = bab_info_unmarshall(data);

  g_assert(info2 != NULL);
  g_assert_cmpint(info2->size, ==, size);
  g_assert_cmpint(info2->mtime, ==, mtime);
  g_assert_cmpstr(info2->filename, ==, "file");
  g_assert_cmpstr((char*)info2->checksum, ==, "ABCDEFGHIJKJMNOPQRSTUVWXYZ012345");

  bab_info_free(info);
  bab_info_free(info2);
}

int main(int argc, char** argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/common/info/marshall", info_marshall_test);
  g_test_add_func("/common/info/unmarshal_roundtrip", info_marshall_roundtrip_test);
  return g_test_run();
}
