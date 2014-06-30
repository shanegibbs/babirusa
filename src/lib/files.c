#include <glib.h>
#include <glib/gstdio.h>
#include <openssl/sha.h>

#include "files.h"

void bab_file_scan(const gchar *p, FileScanCallback callback)
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
        if (g_stat(full, &s) == -1)
        {
            printf("FAILED\n");
            return;
        }

        if (S_ISREG(s.st_mode))
        {
            if (callback != NULL)
            {
                callback(full, &s);
            }
        }
        else if (S_ISDIR(s.st_mode))
        {
            g_debug("Scanning %s", full);
            bab_file_scan(full, callback);
        }
    }
    g_free(full);
    g_dir_close(dir);
}

unsigned char bab_digest_length()
{
    return SHA256_DIGEST_LENGTH;
}

gchar* bab_files_get_sha256_hex(unsigned char *c)
{
    char* str = (char*)g_malloc((2 * SHA256_DIGEST_LENGTH) + 1);
    char* ptr = str;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ptr += sprintf(ptr, "%02x", c[i]);
    }
    *ptr = '\0';

    return str;
}

unsigned char* bab_files_calc_file_hash(gchar *filename)
{
    FILE *inFile = fopen (filename, "rb");
    if (inFile == NULL)
    {
        printf ("%s can't be opened.\n", filename);
        return NULL;
    }

    SHA256_CTX context;
    SHA256_Init(&context);

    int bytes;
    unsigned char data[1024];
    while ((bytes = fread (data, 1, 1024, inFile)) != 0)
        SHA256_Update (&context, data, bytes);

    unsigned char *c = g_malloc(SHA256_DIGEST_LENGTH);
    SHA256_Final(c, &context);

    fclose(inFile);

    return c;
}










