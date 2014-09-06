#include <glib.h>
#include <stdio.h>

#include "info.h"

void print_hex_memory(void *mem, int count)
{
  int i;
  unsigned char *p = (unsigned char *)mem;
  printf("\n");
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

  Info *info = bab_info_new("file", 2, 3, checksum);
  char *data = bab_info_marshall(info);
  bab_info_free(info);

  // print_hex_memory(data, 40);

  g_assert(data != NULL);
  int idx = 0;
  g_assert_cmpint(data[idx++], ==, 40);
  g_assert(data[idx++] == 2);
  g_assert(data[idx++] == 3);
  g_assert(data[idx++] == 4);
  g_assert(data[idx++] == 'f');
  g_assert(data[idx++] == 'i');
  g_assert(data[idx++] == 'l');
  g_assert(data[idx++] == 'e');
  g_assert(data[idx] == 'A');
  g_assert(data[idx + 1] == 'B');
  g_assert(data[idx + 2] == 'C');
  g_assert(data[idx + 31] == '5');
}

void info_unmarshall_test(void)
{
  char data[] = {
    0x28, 0x02, 0x03, 0x04, 0x66, 0x69, 0x6c, 0x65, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
    0x49, 0x4a, 0x4b, 0x4a, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
    0x59, 0x5a, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35
  };

  Info *info = bab_info_unmarshall(data);

  g_assert(info != NULL);
  g_assert_cmpint(info->size, ==, 2);
  g_assert_cmpint(info->mtime, ==, 3);
  g_assert_cmpstr(info->filename, ==, "file");
  g_assert_cmpstr((char*)info->checksum, ==, "ABCDEFGHIJKJMNOPQRSTUVWXYZ012345");

  bab_info_free(info);

}

int main(int argc, char** argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/common/info/marshall", info_marshall_test);
  g_test_add_func("/common/info/unmarshall", info_unmarshall_test);
  return g_test_run();
}
