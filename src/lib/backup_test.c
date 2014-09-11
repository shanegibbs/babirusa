#include <glib.h>
#include <stdio.h>
#include <glib/gstdio.h>

#include <utime.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "backup.h"
#include "files.h"

char *filename = "testfile.bin";
int complete_switch = 0;

static void mock_add(void *self, Info *info)
{
  bab_info_log("add", info);
  g_assert_cmpint(info->size, ==, 25);
  g_assert_cmpint(info->mtime, ==, 1410420084);
  g_assert_cmpstr(info->filename, ==, filename);

  char *checksum = bab_files_get_sha256_hex(info->checksum);
  g_assert_cmpstr(checksum, ==, "02a7926bdce314d86f5faa86b6053b6f2c67ecf7a6b115683cf2a15562886f91");
  complete_switch = 1;
}

void backup_process_files_test(void)
{
  // set some data
  FILE *f = fopen(filename, "w");
  g_assert_nonnull(f);
  fprintf(f, "%s\n", "This is a test file derp");
  fclose(f);

  // set mtime
  struct utimbuf new_times;
  new_times.actime = 1410420084;
  new_times.modtime = 1410420084;
  utime(filename, &new_times);

  // mock reg
  Registry reg = {
    NULL, NULL, mock_add, NULL, NULL
  };

  // get the file stat
  GStatBuf s;
  g_assert_cmpint(g_lstat(filename, &s), !=, -1);

  complete_switch = 0;
  process_file(filename, &s, (void*)&reg);
  g_assert_cmpint(complete_switch, ==, 1);
}

int main(int argc, char** argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/backup/process_file", backup_process_files_test);
  return g_test_run();
}
