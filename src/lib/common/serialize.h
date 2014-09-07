#ifndef SERIALIZE_H
#define SERIALIZE_H

char* to_hex(char *mem, int count);
void serialize_char(char i, char **cur);
void serialize_ulong(unsigned long i, char **cur);

#endif
