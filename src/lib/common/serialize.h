#ifndef SERIALIZE_H
#define SERIALIZE_H

void  to_hex(FILE *stream, char *mem, int count);
char* to_hex_str(char *mem, int count);

void          write_uchar(unsigned char i, char **cur);
unsigned char read_uchar(char **cur);

void  write_bytes(char *bytes, unsigned long count, char **cur);
char* read_bytes(char **cur);

void  write_string(char *str, char **cur);
char* read_string(char **cur);

void          write_ulong(unsigned long i, char **cur);
unsigned long read_ulong(char **cur);

#endif
