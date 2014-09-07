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
    sprintf(tmp, "%02x", p[i]);
    memcpy(output + offset, tmp, 2);
    g_free(tmp);
  }

  return output;
}

void serialize_char(char i, char **cur)
{
  **cur = i;
  (*cur)++;
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
