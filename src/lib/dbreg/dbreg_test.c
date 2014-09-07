#include <glib.h>
#include <stdio.h>

#include "dbreg.h"

void berkely_registry_add_test(void)
{
  Registry *reg = BerkeleyRegistry()->new(NULL);
  g_assert(reg != NULL);

  Checksum *checksum = (Checksum*)"ABCDEFGHIJKJMNOPQRSTUVWXYZ012345";

  Info *info = bab_info_new("myfile", 2, 3, checksum);

  reg->add(reg, info);

  bab_info_free(info);
  reg->free(reg);
}

void berkely_registry_get_test(void)
{
  Registry *reg = BerkeleyRegistry()->new(NULL);
  g_assert(reg != NULL);

  Checksum *checksum = (Checksum*)"ABCDEFGHIJKJMNOPQRSTUVWXYZ012345";
  Info *info_a = bab_info_new("myfile", 2, 3, checksum);

  g_assert_cmpstr(info_a->filename, ==, "myfile");
  g_assert_cmpstr((char*) info_a->checksum, ==, "ABCDEFGHIJKJMNOPQRSTUVWXYZ012345");
  g_assert_cmpint(info_a->size, ==, 2);
  g_assert_cmpint(info_a->mtime, ==, 3);

  reg->add(reg, info_a);

  g_assert_cmpstr(info_a->filename, ==, "myfile");
  g_assert_cmpstr((char*) info_a->checksum, ==, "ABCDEFGHIJKJMNOPQRSTUVWXYZ012345");
  g_assert_cmpint(info_a->size, ==, 2);
  g_assert_cmpint(info_a->mtime, ==, 3);

  Info *info_b = reg->get(reg, "myfile");

  g_assert_cmpstr(info_a->filename, ==, "myfile");
  g_assert_cmpstr((char*) info_a->checksum, ==, "ABCDEFGHIJKJMNOPQRSTUVWXYZ012345");
  g_assert_cmpint(info_a->size, ==, 2);
  g_assert_cmpint(info_a->mtime, ==, 3);

  g_assert(info_b != NULL);
  g_assert(info_b->filename != NULL);
  g_assert(info_b->checksum != NULL);

  g_assert_cmpstr(info_a->filename, ==, info_b->filename);
  g_assert_cmpstr("ABCDEFGHIJKJMNOPQRSTUVWXYZ012345", ==, (char*) info_b->checksum);
  g_assert_cmpint(info_a->size, ==, info_b->size);
  g_assert_cmpint(info_a->mtime, ==, info_b->mtime);

  bab_info_free(info_a);
  bab_info_free(info_b);
  reg->free(reg);
}

int main(int argc, char** argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/dbreg/add", berkely_registry_add_test);
  g_test_add_func("/dbreg/get", berkely_registry_get_test);
  return g_test_run();
}
