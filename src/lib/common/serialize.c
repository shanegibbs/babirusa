#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "serialize.h"

char* to_hex(char *mem, int count)
{
  int char_count = (count * 2) + (count);
  char *output = g_malloc(sizeof(char) * char_count);
  memset(output, ' ', char_count);
  output[char_count - 1] = 0;

  int i;
  unsigned char *p = (unsigned char *)mem;
  for (i = 0; i < count; i++) {
    short offset = i * 3;
    char *tmp = g_malloc(sizeof(char) * 3);
    sprintf(tmp, "%02X", p[i]);
    memcpy(output + offset, tmp, 2);
    g_free(tmp);
  }

  return output;
}

/* long zigzag32(long v)
{
  if (v < 0) {
    return ((long) (-v)) * 2 - 1;
  } else {
    return v * 2;
  }
}*/

void serialize_char(char i, char **cur)
{
  **cur = i;
  (*cur)++;
}

static char read_char(char **cur)
{
  char i = **cur;
  (*cur)++;
  return i;
}

void write_ulong(unsigned long i, char **cur)
{
  while (i >= 0x80) {
    serialize_char(i | 0x80, cur);
    i >>= 7;
  }
  g_assert_cmpint(i, <, 0x80);
  serialize_char(i, cur);
}

unsigned long read_ulong(char **cur)
{
  unsigned long i = 0;
  unsigned char n;
  // printf("i(0)=%lu\n", i);

  int a = 0;
  while ((n = read_char(cur)) >= 0x80) {
    i |= (n & 0x7f) << (a++ * 7);
    // printf("i(1)=%lu\n", i);
    // printf("n=%d\n", n);
  }

  g_assert_cmpint(n, <, 0x80);
  // printf("n=%d\n", n);
  i |= n << (a * 7);
  return i;
}

void serialize_ulong(unsigned long i, char **cur)
{
  gboolean started = FALSE;
  char val;
  short bytes = 0;

  for (int n = 7; n >= 0; n--) {
    val = (i >> (n * 8)) & 0xff;
    if (started == TRUE || val != 0) {
      if (started == FALSE) {
        started = TRUE;
        bytes = n + 1;
        serialize_char(bytes, cur);
      }
      serialize_char(val, cur);
    }
  }

  if (started == FALSE) {
    serialize_char(0, cur);
  }
}
