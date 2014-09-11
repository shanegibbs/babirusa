#ifndef INFO_H
#define INFO_H

#include <glib.h>

typedef unsigned char Checksum;

typedef struct info_struct
{
    gchar *filename;
    unsigned long size;
    long mtime;
    Checksum *checksum;
} Info;

Info* bab_info_new         (gchar *filename, unsigned long size, long mtime, Checksum *checksum);
void  bab_info_free        (Info *info);
void  bab_info_log         (const char* msg, Info *info);
char* bab_info_marshall    (Info *info);
Info* bab_info_unmarshall  (char *data);
long  bab_info_max_size    ();

char ulong_char(unsigned long i, short pos);

#endif
