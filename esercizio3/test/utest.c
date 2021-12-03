#include <stdlib.h>
#include <stdio.h>
#include "hash_map.h"
#include "unity.h"

int compare(void *a, void *b)
{
  return *(int *)a - *(int *)b;
}

void test_create_map()
{
  int size_map = 10;
  float load_factor = 0.3;
  HashMap *map = hash_map_create(size_map, compare, load_factor);
  TEST_ASSERT_EQUAL(map, map);
  hash_map_delete(map);
}

void test_create_map_size_0()
{
  int size_map = 0;
  float load_factor = 0.5;
  HashMap *map = hash_map_create(size_map, compare, load_factor);
  TEST_ASSERT_EQUAL(NULL, map);
  hash_map_delete(map);
}

void test_create_map_compare_null()
{
  int size_map = 10;
  float load_factor = 0.5;
  HashMap *map = hash_map_create(size_map, NULL, load_factor);
  TEST_ASSERT_EQUAL(NULL, map);
  hash_map_delete(map);
}

void test_create_map_load_factor_wrong()
{
  int size_map = 10;
  float load_factor = -5;
  HashMap *map = hash_map_create(size_map, compare, load_factor);
  TEST_ASSERT_EQUAL(NULL, map);
  hash_map_delete(map);
}

void test_hash_map_insert()
{
  int size = 2, val = 3, key = 42;
  float load = 0.95;
  HashMap *map = hash_map_create(size, compare, load);
  TEST_ASSERT_EQUAL(map, map);

  map = hash_map_insert(map, &key, &val);
  TEST_ASSERT_EQUAL(val, *((int *)hash_map_search(map, &key)));
  hash_map_delete(map);
}

void test_hash_map_insert_map_null()
{
  HashMap *map = NULL;
  int key = 3, val = 7;

  TEST_ASSERT_EQUAL(NULL, hash_map_insert(map, &key, &val));
  hash_map_delete(map);
}

void test_hash_map_insert_key_null()
{
  HashMap *map = hash_map_create(2, compare, 0.99);
  TEST_ASSERT_EQUAL(map, map);

  int val = 5;
  
  TEST_ASSERT_EQUAL(NULL, hash_map_insert(map, NULL, &val));
  hash_map_delete(map);
}

void test_hash_map_insert_val_null()
{
  HashMap *map = hash_map_create(2, compare, 0.99);
  TEST_ASSERT_EQUAL(map, map);

  
  int key = 5;

  TEST_ASSERT_EQUAL(NULL, hash_map_insert(map, &key, NULL));
  hash_map_delete(map);
}

void test_hash_map_size_null()
{
  int size_map = -1;
  HashMap *map = hash_map_create(size_map, compare, 0.99);
  
  TEST_ASSERT_EQUAL(NULL, map);
  hash_map_delete(map);
}

void test_hash_map_size()
{
  int size_map = 10;
  HashMap *map = hash_map_create(size_map, compare, 0.99);
  
  TEST_ASSERT_EQUAL(size_map, hash_map_size(map));
  hash_map_delete(map);
}

void test_hash_map_nr_assoc_map_null()
{
  HashMap *map = NULL;

  TEST_ASSERT_EQUAL(-1, hash_map_nr_associations(map));
  hash_map_delete(map);
}

void test_hash_map_nr_assoc()
{
  int key0 = 0, val0 = 0; 
  int key1 = 1, val1 = 2; 
  int size = 5;

  HashMap *map = hash_map_create(size, compare, 0.9);
  TEST_ASSERT_EQUAL(map, map);


  map = hash_map_insert(map, &key0, &val0);
  map = hash_map_insert(map, &key1, &val1);
  
  TEST_ASSERT_EQUAL(map, map);

  TEST_ASSERT_EQUAL(2, hash_map_nr_associations(map));
  
  hash_map_delete(map);
}

void test_hash_map_test_key_map_null()
{
  HashMap *map = NULL;
  int k = 5;

  TEST_ASSERT_EQUAL(FALSE, hash_map_test_key(map, &k));
  hash_map_delete(map);
}

void test_hash_test_key()
{
  int size = 10; 
  int key, val = 5;
  HashMap *map = hash_map_create(size, compare, 0.9);
  
  key = 2;
  map = hash_map_insert(map, &key, &val);
  TEST_ASSERT_EQUAL(TRUE, hash_map_test_key(map, &key));
  
  key = 3;
  TEST_ASSERT_EQUAL(FALSE, hash_map_test_key(map, &key));
  
  key = 12;
  map = hash_map_insert(map, &key, &val);
  TEST_ASSERT_EQUAL(TRUE, hash_map_test_key(map, &key));

  
  hash_map_delete(map);
}

void test_hash_map_search_if_map_null()
{
  HashMap *map = NULL;
  int key = 2;

  TEST_ASSERT_EQUAL(NULL, hash_map_search(map, &key));
  
  hash_map_delete(map);
}

void test_hash_map_search_key_null()
{
  int size = 10;
  HashMap *map = hash_map_create(size, compare, 0.99);
  
  TEST_ASSERT_EQUAL(NULL, hash_map_search(map, NULL));
  
  hash_map_delete(map);
}

void test_hash_map_search()
{
  int size = 10, key, val = 5;
  HashMap *map = hash_map_create(size, compare, 0.99);
  
  key = 2;
  map = hash_map_insert(map, &key, &val);
  TEST_ASSERT_EQUAL(0, compare(hash_map_search(map, &key), &val));
  
  key = 3;
  TEST_ASSERT_EQUAL(NULL, hash_map_search(map, &key));
  
  key = 12;
  val = 42;
  map = hash_map_insert(map, &key, &val);
  TEST_ASSERT_EQUAL(0, compare(hash_map_search(map, &key), &val));

  hash_map_delete(map);
}

void test_hash_map_is_empty()
{
  int size = 4, key = 0, val = 2;
  
  HashMap *map = hash_map_create(size, compare, 0.99);
  TEST_ASSERT_EQUAL(TRUE, hash_map_is_empty(map));

  map = hash_map_insert(map, &key, &val);
  TEST_ASSERT_EQUAL(FALSE, hash_map_is_empty(map));
  
  hash_map_delete(map);
}

void test_hash_map_delete_all()
{
  int size = 2;
  HashMap *map = hash_map_create(size, compare, 0.99);
  TEST_ASSERT_EQUAL(map, map);


  for (int i = 0, v = 0; i < size; i++, v++)
  {
    map = hash_map_insert(map, &i, &v);
  }
  TEST_ASSERT_EQUAL(FALSE, hash_map_is_empty(map));

  hash_map_delete_associations(map);
  TEST_ASSERT_EQUAL(TRUE, hash_map_is_empty(map));
  
  hash_map_delete(map);
}

void test_hash_map_delete_item_if_map_is_null()
{
  HashMap *map = NULL;
  int k = 5;

  TEST_ASSERT_EQUAL(NULL, hash_map_delete_item(map, &k));

  hash_map_delete(map);
}

void test_hash_map_delete_item_if_map_key_is_null()
{
  int size = 1, key, val;
  HashMap *map = hash_map_create(size, compare, 0.99);
  
  TEST_ASSERT_EQUAL(map, map);

  
  key = 0;
  val = 2;
  map = hash_map_insert(map, &key, &val);

  TEST_ASSERT_EQUAL(NULL, hash_map_delete_item(map, NULL));
  
  hash_map_delete(map);
}

void test_hash_map_delete_item()
{
  int size = 1, key, val;
  HashMap *map = hash_map_create(size, compare, 0.99);
  
  TEST_ASSERT_EQUAL(map, map);


  key = 0;
  val = 2;
  map = hash_map_insert(map, &key, &val);
  map = hash_map_delete_item(map, &key);

  TEST_ASSERT_EQUAL(TRUE, hash_map_is_empty(map));
 
  hash_map_delete(map);
}

void test_hash_map_key_used()
{
  int key1, val1, key2, val2;
  key1 = 1;
  val1 = 1;
  key2 = 2;
  val2 = 2;
  
  HashMap *map = hash_map_create(2, compare, 0.99);
  
  TEST_ASSERT_EQUAL(map, map);

  
  map = hash_map_insert(map, &key1, &val1);
  map = hash_map_insert(map, &key2, &val2);
  
  void **key = hash_map_keys_used(map);
  
  TEST_ASSERT_EQUAL(2, *((int *)key[1]));
  TEST_ASSERT_EQUAL(1, *((int *)key[0]));

  hash_map_delete(map);
  free(key);
}

void test_hash_map_undersized()
{
  int ka, kb, kc;
  int va, vb, vc;
  size_t size = 1;
  
  va = 1, ka = 1, vb = 1, kb = 2, vc = 1, kc = 3;
  
  HashMap *map = hash_map_create(size, compare, 0.99);
  
  TEST_ASSERT_EQUAL(map, map);


  map = hash_map_insert(map, &ka, &va);
  map = hash_map_insert(map, &kb, &vb);
  map = hash_map_insert(map, &kc, &vc);
  
  TEST_ASSERT_EQUAL(TRUE, hash_map_test_key(map, &ka));
  TEST_ASSERT_EQUAL(TRUE, hash_map_test_key(map, &kb));
  TEST_ASSERT_EQUAL(TRUE, hash_map_test_key(map, &kc));
  
  hash_map_delete(map);
}

void test_hash_map_resize()
{
  int size = 2;
  HashMap *map = hash_map_create(size, compare, 0.49);

  TEST_ASSERT_EQUAL(map, map);


  int key = 2;
  int val = 42;
  map = hash_map_insert(map, &key, &val);

  int key1 = 4;
  int val1 = 25;
  map = hash_map_insert(map, &key1, &val1);
  
  TEST_ASSERT_EQUAL(4, hash_map_size(map));
  
  hash_map_delete(map);
}


int main()
{

  UNITY_BEGIN();

  RUN_TEST(test_create_map);
  RUN_TEST(test_create_map_size_0);
  RUN_TEST(test_create_map_compare_null);
  RUN_TEST(test_create_map_load_factor_wrong);

  RUN_TEST(test_hash_map_insert);
  RUN_TEST(test_hash_map_insert_map_null);
  RUN_TEST(test_hash_map_insert_key_null);
  RUN_TEST(test_hash_map_insert_val_null);

  RUN_TEST(test_hash_map_size);
  RUN_TEST(test_hash_map_size_null);

  RUN_TEST(test_hash_map_nr_assoc);
  RUN_TEST(test_hash_map_nr_assoc_map_null);

  RUN_TEST(test_hash_test_key);
  RUN_TEST(test_hash_map_test_key_map_null);

  RUN_TEST(test_hash_map_search);
  RUN_TEST(test_hash_map_search_key_null);
  RUN_TEST(test_hash_map_search_if_map_null);

  RUN_TEST(test_hash_map_is_empty);

  RUN_TEST(test_hash_map_delete_all);
  RUN_TEST(test_hash_map_delete_item);
  RUN_TEST(test_hash_map_delete_item_if_map_is_null);
  RUN_TEST(test_hash_map_delete_item_if_map_key_is_null);

  RUN_TEST(test_hash_map_key_used);
  RUN_TEST(test_hash_map_undersized);
  RUN_TEST(test_hash_map_resize);

  UNITY_END();

}