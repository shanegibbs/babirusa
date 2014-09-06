#include <glib.h>
#include <stdio.h>

#include "dbreg.h"

void berkely_registry_add_test(void)
{
  Registry *reg = BerkeleyRegistry()->new(NULL);
  g_assert(reg != NULL);

  Checksum *checksum = (Checksum*)"123abc";

  Info *info = bab_info_new("myfile", 100, 250, checksum);

  reg->add(reg, info);

  bab_info_free(info);
  reg->free(reg);
}

void berkely_registry_get_test(void)
{
  Registry *reg = BerkeleyRegistry()->new(NULL);
  g_assert(reg != NULL);

  Checksum *checksum = (Checksum*)"123abc";

  Info *info = bab_info_new("myfile", 100, 250, checksum);

  reg->add(reg, info);

  bab_info_free(info);
  reg->free(reg);
}

int main(int argc, char** argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/dbreg/add", berkely_registry_add_test);
  g_test_add_func("/dbreg/get", berkely_registry_get_test);
  return g_test_run();
}
