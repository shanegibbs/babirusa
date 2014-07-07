#include <glib.h>
#include <glib/gstdio.h>
#include <openssl/sha.h>
#include <string.h>
#include <errno.h>

#include "files.h"
#include "info.h"

GQuark bab_files_error_quark()
{
    return g_quark_from_static_string("bab-files-error-quark");
}

void bab_file_scan(const gchar *p, FileScanCallback callback, void *data)
{
    g_assert(p != NULL);

    GError *err = NULL;

    GDir *dir = g_dir_open(p, 0, &err);
    if (err != NULL)
    {
        g_assert(dir == NULL);
        fprintf(stderr, "%s\n", err->message);
        g_error_free(err);
        return;
    }
    g_assert(dir != NULL);

    const gchar *d;
    gchar *full = g_malloc(1024);
    while ((d = g_dir_read_name(dir)) != NULL)
    {
        sprintf(full, "%s/%s", p, d);

        GStatBuf s;

        if (g_lstat(full, &s) == -1)
        {
            gchar* error_str = strerror(errno);
            g_warning("Failed to stat file %s: %s\n", full, error_str);
            return;
        }

        if (S_ISREG(s.st_mode))
        {
            if (callback != NULL)
            {
                callback(full, &s, data);
            }
        }
        else if (S_ISLNK(s.st_mode))
        {
            g_message("Skipping link %s", full);
        }
        else if (S_ISDIR(s.st_mode))
        {
            g_debug("Scanning %s", full);
            bab_file_scan(full, callback, data);
        }
    }
    g_free(full);
    g_dir_close(dir);
}

unsigned char bab_digest_length()
{
    return g_checksum_type_get_length(G_CHECKSUM_SHA256);
}

gchar* bab_files_get_sha256_hex(unsigned char *c)
{
    g_assert(c != NULL);

    char* str = (char*)g_malloc((2 * bab_digest_length()) + 1);
    char* ptr = str;
    for (int i = 0; i < bab_digest_length(); i++)
    {
        ptr += sprintf(ptr, "%02x", c[i]);
    }
    *ptr = '\0';

    return str;
}

Checksum* bab_files_calc_file_hash(gchar *filename, GError **err)
{
    FILE *inFile = fopen(filename, "rb");
    if (inFile == NULL)
    {
        gchar* error_str = strerror(errno);
        g_set_error(err, BAB_FILES_ERROR, BAB_FILES_ERROR_OPEN_FAILED, "%s", error_str);
        return NULL;
    }

    GChecksum *checksum = g_checksum_new(G_CHECKSUM_SHA256);

    int bytes;
    unsigned char data[1024];
    while ((bytes = fread (data, 1, 1024, inFile)) != 0)
    {
        g_checksum_update(checksum, data, bytes);
    }

    gsize buflen = bab_digest_length();
    unsigned char *c = g_malloc(bab_digest_length());
    g_checksum_get_digest(checksum, c, &buflen);
    g_checksum_free(checksum);

    fclose(inFile);

    g_assert(c != NULL);
    return c;
}











