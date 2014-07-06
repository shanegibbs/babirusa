#ifndef INFO_H
#define INFO_H

#include <glib.h>

typedef unsigned char Checksum;

typedef struct info_struct
{
    gchar *filename;
    int size;
    int mtime;
    Checksum *checksum;
} Info;

Info* bab_info_new  (gchar *filename, int size, int mtime, Checksum *checksum);
void  bab_info_free (Info *info);
void  bab_info_log  (Info *info);

#endif
