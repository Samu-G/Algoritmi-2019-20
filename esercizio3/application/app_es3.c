#include "hash_map.h"
#include <string.h>
#include <time.h>
#define DIM_KEYS 10000000

typedef struct _Data
{
  int key;
  int val;
} Data;

int count_rows(const char *name_file)
{
  if (name_file == NULL)
    return -1;
  FILE *ptr_file;
  if ((ptr_file = fopen(name_file, "r")) == NULL)
  {
    return -1;
  }
  else
  {
    int nr_rows = 0;
    for (char c = getc(ptr_file); c != EOF; c = getc(ptr_file))
    {
      if (c == '\n')
        nr_rows++;
    }
    fclose(ptr_file);
    return nr_rows;
  }
}

int data_cmp_key(const void *a, const void *b)
{
  Data *sup_a = (Data *)a;
  Data *sup_b = (Data *)b;
  return sup_a->key - sup_b->key;
}

int *random_array_new(size_t size, int low_limit, int high_limit, unsigned int srand_seed)
{
  int *res;
  if (size <= 0)
  {
    res = NULL;
  }
  else
  {
    res = malloc(sizeof(int) * size);
    srand(srand_seed);
    for (int i = 0; i < size; i++)
    {
      res[i] = rand() % (high_limit - low_limit + 1) + low_limit;
    }
  }
  return res;
}

int nr_val_searched_array(int *keys, size_t dim_key, Data *vett, size_t size_vett)
{
  if (vett == NULL || keys == NULL)
    return -1;
  int nr_values = 0;
  for (int i = 0; i < dim_key; i++)
  {
    if (bsearch(&keys[i], vett, size_vett, sizeof(Data), data_cmp_key) != NULL)
      nr_values++;
  }
  return nr_values;
}

int nr_val_searched_hash_map(int *keys, size_t dim_key, HashMap *map, size_t size_map)
{
  if (keys == NULL || dim_key <= 0 || map == NULL || size_map <= 0)
    return -1;
  int nr_val = 0;
  for (int i = 0; i < dim_key; i++)
  {
    if (hash_map_search(map, &keys[i]) != NULL)
      nr_val++;
  }
  return nr_val;
}

int cmp(void *a, void *b)
{
  return *((int *)a) - *((int *)b);
}

Data *load_array(const char *name_file)
{
  if (name_file == NULL)
    return NULL;

  int size = count_rows(name_file);
  int nr_arg = 0;
  Data *d = malloc(sizeof(Data) * size);
  FILE *fp;
  int key = 0, val = 0;

  if ((fp = fopen(name_file, "r")) == NULL)
  {
    printf("File not found\n");
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; !feof(fp); i++)
  {
    nr_arg = fscanf(fp, "%d,%d\n", &key, &val);
    if (nr_arg != 2)
    {
      printf("Error reading line at %ld\n", i);
      return NULL;
    }
    d[i].key = key;
    d[i].val = val;
  }
  fclose(fp);
  return d;
}

HashMap *load_hash_map(const char *name_file, size_t size)
{
  clock_t start_t, end_t;

  start_t = clock();
  Data *entries = load_array(name_file);
  end_t = clock();
  printf("\nElapsed time to copy file data to memory: %f seconds", (double)(end_t - start_t) / CLOCKS_PER_SEC);

  start_t = clock();
  if (entries == NULL)
  {
    printf("error load array entries\n");
    exit(EXIT_FAILURE);
  }
  HashMap *map = hash_map_create(size, cmp, 2);
  if (map == NULL)
  {
    perror("error create the hash map named map\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < size; i++)
  {
    if (hash_map_insert(map, &entries[i].key, &entries[i].val) == NULL)
    {
      printf("problem with the insert of the <%d, %d> at line %d", entries[i].key, entries[i].val, i);
      return NULL;
    }
  }
  end_t = clock();
  printf("\nElapsed time to setting up the hash-map: %f seconds", (double)(end_t - start_t) / CLOCKS_PER_SEC);

  return map;
}

int main()
{
  Data *array;
  HashMap *map;
  clock_t start_t, end_t;
  char name_file[20];
  unsigned int seed = 45;
  int nr_rows, nr_elements_find_array, nr_elements_find_hash_map;
  int *keys;

  printf("\n\n\n\n||   Hash-Map  speed test   ||\n|| Created by S.G. and M.B. ||\n\n\n\n");

  puts("Please insert file name: ");
  scanf("%s", name_file);
  nr_rows = count_rows(name_file);

  printf("\n\n\nLoading file into Hash-Map-------------------------------------");
  start_t = clock();
  map = load_hash_map(name_file, nr_rows);
  end_t = clock();
  printf("\nELAPSED TIME: %f seconds", (double)(end_t - start_t) / CLOCKS_PER_SEC);

  printf("\n\n\nLoading file into a static vector------------------------------");
  start_t = clock();
  array = load_array(name_file);
  end_t = clock();
  printf("\nELAPSED TIME: %f seconds", (double)(end_t - start_t) / CLOCKS_PER_SEC);

  qsort(array, nr_rows, sizeof(Data), data_cmp_key);
  keys = random_array_new(10000000, 0, 10000000, seed);

  printf("\n\n\nReseatching on Hash-Map----------------------------------------");
  start_t = clock();
  nr_elements_find_hash_map = nr_val_searched_hash_map(keys, DIM_KEYS, map, nr_rows);
  end_t = clock();
  printf("\nELAPSED TIME: %f seconds", (double)(end_t - start_t) / CLOCKS_PER_SEC);

  printf("\n\n\nResearching on static vector using binary-research-------------");
  start_t = clock();
  nr_elements_find_array = nr_val_searched_array(keys, DIM_KEYS, array, nr_rows);
  end_t = clock();
  printf("\nELAPSED TIME: %f seconds", (double)(end_t - start_t) / CLOCKS_PER_SEC);

  printf("\n\n\n");
  if (nr_elements_find_array == nr_elements_find_hash_map)
  {
    printf("Number of keys successfully found is the same in both tests\n");
  }
  else
  {
    printf("Number of keys successfully found is NOT the same in both tests\n");
  }
  printf("\n\n");

  free(keys);
  free(array);
  hash_map_delete(map);
}