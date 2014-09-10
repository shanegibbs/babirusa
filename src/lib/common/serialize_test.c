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

  n = 4850832165;
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

void serialize_ulong_test(void)
{
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
  unsigned long x;
  for (unsigned short i = 0; i < 64; i++) {
    x = pow(2, i);

    memset(data, 0, size);

    cur = data;
    write_ulong(x, &cur);

    cur = data;
    n = read_ulong(&cur);

    if (n != x) g_assert_cmpint(n, ==, x);
  }

}

int main(int argc, char** argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/common/serialize/ulong_basic", serialize_ulong_basic_test);
  g_test_add_func("/common/serialize/ulong", serialize_ulong_test);

  return g_test_run();
}
