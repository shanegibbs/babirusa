#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "serialize.h"

void serialize_ulong_test(void)
{
  printf("\n");

  int char_count = 9;
  size_t size = sizeof(char) * char_count;
  char *data = g_malloc(size);
  char *cur = data;

  cur = data;
  memset(data, 0, size);
  serialize_ulong(0, &cur);
  g_assert_cmpstr(to_hex(data, char_count), ==, "00 00 00 00 00 00 00 00 00");

  cur = data;
  memset(data, 0, size);
  serialize_ulong(1, &cur);
  g_assert_cmpstr(to_hex(data, char_count), ==, "01 01 00 00 00 00 00 00 00");

  cur = data;
  memset(data, 0, size);
  serialize_ulong(pow(2, 4), &cur);
  g_assert_cmpstr(to_hex(data, char_count), ==, "01 10 00 00 00 00 00 00 00");

  cur = data;
  memset(data, 0, size);
  serialize_ulong(pow(2, 8), &cur);
  g_assert_cmpstr(to_hex(data, char_count), ==, "02 01 00 00 00 00 00 00 00");

  cur = data;
  memset(data, 0, size);
  serialize_ulong(pow(2, 12), &cur);
  g_assert_cmpstr(to_hex(data, char_count), ==, "02 10 00 00 00 00 00 00 00");

  cur = data;
  memset(data, 0, size);
  serialize_ulong(pow(2, 16), &cur);
  g_assert_cmpstr(to_hex(data, char_count), ==, "03 01 00 00 00 00 00 00 00");

  cur = data;
  memset(data, 0, size);
  serialize_ulong(pow(2, 32), &cur);
  g_assert_cmpstr(to_hex(data, char_count), ==, "05 01 00 00 00 00 00 00 00");

  cur = data;
  memset(data, 0, size);
  serialize_ulong(-1, &cur);
  g_assert_cmpstr(to_hex(data, char_count), ==, "08 ff ff ff ff ff ff ff ff");

  cur = data;
  memset(data, 0, size);
  serialize_ulong(1024 * 1024 * 10, &cur);
  g_assert_cmpstr(to_hex(data, char_count), ==, "03 a0 00 00 00 00 00 00 00");

}

int main(int argc, char** argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/common/serialize/ulong", serialize_ulong_test);
  return g_test_run();
}
