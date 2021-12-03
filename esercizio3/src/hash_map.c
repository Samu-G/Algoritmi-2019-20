#include "../include/hash_map.h"

typedef struct _HashEntry
{
  void *key;
  void *value;
  struct _HashEntry *next;
} HashEntry;

typedef struct _HashMap
{
  HashEntry **entries;
  HashCmp cmp;
  float load_factor;
  size_t size;
  int nr_elements;
} HashMap;

int hash_code(void *key, int size)
{
  return *(int *)key % size;
}

HashMap *hash_map_create(size_t size, HashCmp compare, const float load_factor)
{
  if (size <= 0 || compare == NULL || load_factor <= 0.25)
    return NULL;

  if (load_factor <= 0.49)
  {
    puts("WARNING: load factor less than 0.49 causes inefficiencies\n");
  }
  
  HashMap *map = (HashMap *)malloc(sizeof(HashMap));

  if (map == NULL)
  {
    perror("Pointer of the hash map null. hash_map_create ERR\n");
    return NULL;
  }

  map->entries = (HashEntry **)malloc(sizeof(HashEntry *) * size);

  if (map->entries == NULL)
    return NULL;

  for (int i = 0; i < size; i++)
    map->entries[i] = NULL;

  map->nr_elements = 0;
  map->size = size;
  map->cmp = compare;
  map->load_factor = load_factor;
  return map;
}

void hash_map_delete(HashMap *map)
{
  if (map != NULL && map->nr_elements > 0)
  {
    for (size_t i = 0; i < map->size; i++)
    {
      if (map->entries[i] != NULL)
      {
        HashEntry *ptr = map->entries[i];
        HashEntry *prev;
        while (ptr != NULL)
        {
          ptr->key = NULL;
          ptr->value = NULL;
          prev = ptr;
          ptr = ptr->next;
          free(prev);
        }
      }
    }
    free(map);
  }
}

int hash_map_is_empty(HashMap *map)
{
  if (map == NULL)
  {
    puts("Map passed by argument equal to NULL. hash_map_is_empty ERR\n");
    return -1;
  }
  else
  {
    return (hash_map_nr_associations(map) == 0) ? (TRUE) : (FALSE);
  }
}

int hash_map_nr_associations(HashMap *map)
{
  return (map == NULL) ? (-1) : (map->nr_elements);
}

void hash_map_delete_associations(HashMap *map)
{
  if (map != NULL)
  {
    for (int i = 0; i < map->size; i++)
      free(map->entries[i]);
    map->nr_elements = 0;
  }
  else
  {
    puts("Map passed by argument equal to NULL. hash_map_delete_associations ERR\n");
  }
}

int hash_map_test_key(HashMap *map, void *key)
{
  if (map == NULL || key == NULL)
    return FALSE;

  int i = hash_code(key, map->size);
  HashEntry *entry = map->entries[i];

  if (entry == NULL)
    return FALSE;

  while (entry != NULL)
  {
    if (map->cmp(key, entry->key) == 0)
      return TRUE;

    entry = entry->next;
  }
  return FALSE;
}

HashMap *hash_map_insert(HashMap *map, void *key, void *value)
{
  if (key == NULL || value == NULL || map == NULL)
  {
    puts("\nOne of the parameters equal to NULL. hash_map_insert ERR");
    return NULL;
  }

  int i = hash_code(key, map->size);
  HashEntry *entry = map->entries[i];
  float load;
  if (entry == NULL)
  {
    map->entries[i] = sup_insert(key, value);
    map->nr_elements++;
  }
  else
  {
    HashEntry *prec = entry;

    while (entry != NULL)
    {
      if (map->cmp(entry->key, key) == 0)
      {
        entry->value = (void *)malloc(sizeof(value));
        entry->value = value;
      }
      prec = entry;
      entry = entry->next;
    }

    map->nr_elements++;
    prec->next = sup_insert(key, value);
  }

  load = map->nr_elements / map->size;
  if (load > map->load_factor)
    map = realloc_map(map, map->size * 2);

  return map;
}

void *hash_map_search(HashMap *map, void *key)
{
  if (map == NULL || key == NULL)
  {
    puts("\nOne of the parameters equal to NULL. hash_map_search ERR");
    return NULL;
  }

  if (hash_map_test_key(map, key) == FALSE)
    return NULL;

  int i = hash_code(key, map->size);
  HashEntry *entry = map->entries[i];
  while (entry != NULL)
  {
    if (map->cmp(entry->key, key) == 0)
      return entry->value;

    entry = entry->next;
  }
  return NULL;
}

HashMap *hash_map_delete_item(HashMap *map, void *key)
{
  if (map == NULL || key == NULL || map->nr_elements == 0)
  {
    puts("\nMap equal to NULL. hash_map_delete_item ERR");
    return NULL;
  }
  else
  {
    if (hash_map_test_key(map, key) == TRUE)
    {
      int index;

      index = hash_code(key, map->size);
      map->entries[index] = sup_delete(map, map->entries[index], key);

      if ((map->nr_elements / map->size) <= 0.25)
      {
        map = realloc_map(map, map->size * 0.5);
      }
    }
    else
    {
      puts("Key isn't loaded into the map. hash_map_delete_item ERR\n");
    }
    return map;
  }
}

void **hash_map_keys_used(HashMap *map)
{
  if (map->nr_elements == 0 || map == NULL)
  {
    if (map == NULL)
      puts("Map passed by argument equal to NULL. hash_map_keys_used ERR\n");
    return NULL;
  }

  void **keys = (void **)malloc(sizeof(void *) * map->nr_elements);

  if (keys == NULL)
  {
    perror("Malloc error with **keys. hash_map_keys_used ERR\n");
    return NULL;
  }

  HashEntry *entry;
  int j = 0;

  for (int i = 0; i < map->size; i++)
  {
    entry = map->entries[i];
    while (entry != NULL)
    {
      keys[j] = entry->key;
      entry = entry->next;
      j++;
    }
  }
  return keys;
}

HashMap *realloc_map(HashMap *map, size_t new_size)
{
  HashMap *new_map = hash_map_create(new_size, map->cmp, map->load_factor);
  if (new_map == NULL)
  {
    puts("Error during reallocation of the map. realloc_map ERR\n");
    exit(EXIT_FAILURE);
  }
  void **keys = hash_map_keys_used(map);

  int dim_keys = map->nr_elements;

  for (int i = 0; i < dim_keys; i++)
  {
    new_map = hash_map_insert(new_map, keys[i], hash_map_search(map, keys[i]));
  }

  return new_map;
}

int hash_map_size(HashMap *map)
{
  if (map != NULL)
  {
    return map->size;
  }
  else
  {
    puts("Map passed by argument equal to NULL. hash_map_size ERR\n");
    return -1;
  }
}

void hash_map_status(HashMap *map)
{
  if (map == NULL)
  {
    puts("Map passed by argument equal to NULL. hash_map_status ERR\n");
  }
  else
  {
    printf("Dim:\t%ld\nNr elements:\t%d\n", map->size, map->nr_elements);
  }
}

HashEntry *sup_insert(void *key, void *value)
{
  HashEntry *element = (HashEntry *)malloc(sizeof(HashEntry));
  element->key = key;
  element->value = value;
  element->next = NULL;
  return element;
}

HashEntry *sup_delete(HashMap *map, HashEntry *head, void *key)
{
  if (head == NULL)
  {
    return head;
  }
  else if (map->cmp(head->key, key) == 0)
  {
    map->nr_elements--;
    return head->next;
  }
  else
  {
    head->next = sup_delete(map, head->next, key);
    return head;
  }
}