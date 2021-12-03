#include <stdlib.h>
#include <stdio.h>
#include "sorting_lib.h"
#include "record_lib.h"
#include "unity.h"

int cmp(void **obj, int a, int b)
{
  return obj[a] - obj[b];
}

void test_insertion_sort_array_0_elements()
{
  const int SIZE = 0;
  int *v;
  v = malloc(sizeof(int) * SIZE);

  void **ptr = malloc(sizeof(void **));

  for (int i = 0; i < SIZE; i++)
  {
    ptr[i] = malloc(sizeof(void *));
    ptr[i] = (v + i);
  }

  TEST_ASSERT_EQUAL(-1, insertion_sort(ptr, 0, cmp));

  free(ptr);
}

void test_quick_sort_array_0_elements()
{
  const int SIZE = 0;
  int *v;
  v = malloc(sizeof(int) * SIZE);

  void **ptr = malloc(sizeof(void **));

  for (int i = 0; i < SIZE; i++)
  {
    ptr[i] = malloc(sizeof(void *));
    ptr[i] = (v + i);
  }

  TEST_ASSERT_EQUAL(-1, quick_sort(ptr, 0, cmp));

  free(ptr);
}

void test_insertion_sort_array_NULL()
{
  void **ptr = NULL;
  TEST_ASSERT_EQUAL(-1, insertion_sort(ptr, 1, cmp));
}

void test_quick_sort_array_NULL()
{
  void **ptr = NULL;
  TEST_ASSERT_EQUAL(-1, quick_sort(ptr, 1, cmp));
}

void test_record_insert()
{
  Record *a = record_new(1);
  int id = 5, nr_intero = 2;
  float nr_razionale = 5.4;
  char string[10];
  strcpy(string, "test");
  record_insert(a, id, string, nr_intero, nr_razionale);

  TEST_ASSERT_EQUAL(1, (a + id)->id == id);
  TEST_ASSERT_EQUAL(0, strcmp((a + id)->field1, string));
  TEST_ASSERT_EQUAL(1, (a + id)->field2 == nr_intero);
  TEST_ASSERT_EQUAL(1, (a + id)->field3 == nr_razionale);

  record_remove(a);
}
void test_rows_count_wrong_file_name()
{
  TEST_ASSERT_EQUAL(-1, rows_count("greeday.c"));
}

void test_row_count_correct_file_name()
{
  TEST_ASSERT_EQUAL(101, rows_count("Utest_file_dont_delete.txt"));
}

void test_load_file()
{
  Record *a = record_new(1);
  Record *b = record_new(1);
  int dim;
  a = record_load_file("Utest_file_dont_delete.txt", &dim);
  record_insert(b, 0, "noto", 233460, 32209.073312);

  TEST_ASSERT_EQUAL(1, a->id == b->id);
  TEST_ASSERT_EQUAL(0, strcmp(a->field1, b->field1));
  TEST_ASSERT_EQUAL(1, a->field2 == b->field2);
  TEST_ASSERT_EQUAL(1, a->field3 == b->field3);

  record_remove(a);
  record_remove(b);
}

int main()
{

  UNITY_BEGIN();

  RUN_TEST(test_insertion_sort_array_0_elements);
  RUN_TEST(test_quick_sort_array_0_elements);
  RUN_TEST(test_insertion_sort_array_NULL);
  RUN_TEST(test_quick_sort_array_NULL);
  RUN_TEST(test_record_insert);
  RUN_TEST(test_rows_count_wrong_file_name);
  RUN_TEST(test_row_count_correct_file_name);
  RUN_TEST(test_load_file);

  UNITY_END();
}
