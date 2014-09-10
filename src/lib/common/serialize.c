#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "serialize.h"

void to_hex(FILE *stream, char *mem, int count)
{
  char *output = to_hex_str(mem, count);
  fprintf(stream, "%s\n", output);
  g_free(output);
}

char* to_hex_str(char *mem, int count)
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

void write_uchar(unsigned char i, char **cur)
{
  // printf("Writing uchar 0x%0X\n", i);
  **cur = i;
  (*cur)++;
}

unsigned char read_uchar(char **cur)
{
  unsigned char i = **cur;
  // printf("Reading uchar 0x%0X\n", i);
  (*cur)++;
  return i;
}

/*
LSB, 7 bits at a time
*/
void write_ulong(unsigned long i, char **cur)
{
  unsigned char next;
  while (i >= 0x80) {
    next = (i | 0x80) & 0xff;
    // printf("Write next is %0X\n", (unsigned char)i);
    write_uchar(i | 0x80, cur);
    i >>= 7;
  }
  g_assert_cmpint(i, <, 0x80);
  // printf("Write last is %0X\n", (unsigned char)i);
  write_uchar(i, cur);
}

unsigned long read_ulong(char **cur)
{
  unsigned long i = 0;
  unsigned char n;

  unsigned short a = 0;
  while ((n = read_uchar(cur)) >= 0x80) {
    i |= (n & 0x7f) << (a++ * 7);
  }

  g_assert_cmpint(n, <, 0x80);
  i |= (unsigned long)n << (a * 7);
  return i;
}
