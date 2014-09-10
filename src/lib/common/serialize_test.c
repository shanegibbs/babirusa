#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "serialize.h"

void serialize_ulong_basic_test(void)
{
  int char_count = 20;
  size_t size = sizeof(char) * char_count;
  char *data = g_malloc(size);
  char *cur = data;

  // 0
  memset(data, 0, size);
  cur = data;
  write_ulong(0, &cur);
  g_assert_cmpint(cur - data, ==, 1);
  g_assert_cmpstr(to_hex_str(data, 2), ==, "00 00");

  memset(data, 0, size);
  cur = data;
  write_ulong(0, &cur);
  cur = data;
  g_assert_cmpint(read_ulong(&cur), ==, 0);

  // 1
  memset(data, 0, size);
  cur = data;
  write_ulong(1, &cur);
  g_assert_cmpint(cur - data, ==, 1);
  g_assert_cmpstr(to_hex_str(data, 2), ==, "01 00");

  memset(data, 0, size);
  cur = data;
  write_ulong(1, &cur);
  cur = data;
  g_assert_cmpint(read_ulong(&cur), ==, 1);

  // 300
  memset(data, 0, size);
  cur = data;
  write_ulong(300, &cur);
  g_assert_cmpint(cur - data, ==, 2);
  g_assert_cmpstr(to_hex_str(data, 3), ==, "AC 02 00");

  memset(data, 0, size);
  cur = data;
  write_ulong(300, &cur);
  cur = data;
  g_assert_cmpint(read_ulong(&cur), ==, 300);

  unsigned long n;
  unsigned long x;

  // > int
  n = UINT_MAX;
  memset(data, 0, size);
  cur = data;
  write_ulong(n, &cur);
  cur = data;
  g_assert_cmpint(read_ulong(&cur), ==, n);

  n = UINT_MAX + 1;
  memset(data, 0, size);
  cur = data;
  write_ulong(n, &cur);
  cur = data;
  g_assert_cmpint(read_ulong(&cur), ==, n);

  n = UINT_MAX * 2;
  memset(data, 0, size);
  cur = data;
  write_ulong(n, &cur);
  cur = data;
  g_assert_cmpint(read_ulong(&cur), ==, n);

  n = ULONG_MAX;
  memset(data, 0, size);
  cur = data;
  write_ulong(n, &cur);
  g_assert_cmpint(cur - data, ==, 10);
  cur = data;
  g_assert_cmpint(read_ulong(&cur), ==, n);

  n = 75794252602;
  memset(data, 0, size);
  cur = data;
  write_ulong(n, &cur);
  cur = data;
  x = read_ulong(&cur);
  if (x != n) {
    printf("FAILED expected %lu, got %lu\n", n, x);
    g_assert_cmpint(x, ==, n);
  }
}

void serialize_ulong_hard_test(void)
{
  int char_count = 40;
  size_t size = sizeof(char) * char_count;
  char *data = g_malloc(size);
  char *cur = data;

  unsigned long test_value = 4850832165;
  // unsigned long test_value = 300;

  cur = data;
  memset(data, 0, size);
  write_ulong(test_value, &cur);
  printf("%lu\n", cur - data);
  // to_hex(stdout, data, 8);
  cur = data;
  unsigned long x = read_ulong(&cur);
  printf("%lu\n", cur - data);
  g_assert_cmpint(x, ==, test_value);
}

void serialize_ulong_test(void)
{
  printf("\n");

  int char_count = 20;
  size_t size = sizeof(char) * char_count;
  char *data = g_malloc(size);
  char *cur = data;

  cur = data;
  memset(data, 0, size);
  write_ulong(1, &cur);
  g_assert_cmpint(cur - data, ==, 1);
  g_assert_cmpstr(to_hex_str(data, 2), ==, "01 00");

  cur = data;
  memset(data, 0, size);
  write_ulong(300, &cur);
  g_assert_cmpint(cur - data, ==, 2);
  g_assert_cmpstr(to_hex_str(data, 3), ==, "AC 02 00");

  cur = data;
  memset(data, 0, size);
  write_ulong(1, &cur);
  g_assert_cmpint(read_ulong(&data), ==, 1);

  cur = data;
  memset(data, 0, size);
  write_ulong(300, &cur);
  g_assert_cmpint(read_ulong(&data), ==, 300);

  unsigned long n;
  for (unsigned long i = 0; i < ULONG_MAX; i = (i + 1) * 2.5) {
    printf("%lu\n", i);
    memset(data, 0, size);

    cur = data;
    write_ulong(i, &cur);

    cur = data;
    n = read_ulong(&cur);

    if (n != i) g_assert_cmpint(n, ==, i);
  }

  /*
  cur = data;
  memset(data, 0, size);
  serialize_ulong(1000, &cur);
  g_assert_cmpstr(to_hex(data, char_count), ==, "00 00 00 00 00 00 00 00 00");

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
  */

}

int main(int argc, char** argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/common/serialize/ulong_basic", serialize_ulong_basic_test);
  g_test_add_func("/common/serialize/ulong_hard", serialize_ulong_hard_test);
  g_test_add_func("/common/serialize/ulong", serialize_ulong_test);

  return g_test_run();
}
