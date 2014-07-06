#include <glib.h>
#include <glib/gstdio.h>

#include "info.h"

#define BAB_FILES_ERROR bab_files_error_quark()

enum BabFilesError
{
    BAB_FILES_ERROR_OPEN_FAILED
};

typedef void (*FileScanCallback)(gchar*, struct stat*, void *data);

void           bab_file_scan            (const gchar *p, FileScanCallback callback, void *data);
unsigned char  bab_digest_length        ();
gchar*         bab_files_get_sha256_hex (unsigned char *c);
Checksum* bab_files_calc_file_hash (gchar *filename, GError**);
