#include <glib.h>
#include <glib/gstdio.h>

typedef void (*FileScanCallback)(gchar*, struct stat*);

void           bab_file_scan            (const gchar *p, FileScanCallback callback);
unsigned char  bab_digest_length        ();
gchar*         bab_files_get_sha256_hex (unsigned char *c);
unsigned char* bab_files_calc_file_hash (gchar *filename);
