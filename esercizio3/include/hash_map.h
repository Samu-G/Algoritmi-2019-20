#pragma once

#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1

typedef struct _HashEntry HashEntry;
typedef struct _HashMap HashMap;
typedef int (*HashCmp)(void *, void *);

/*Allocates memory and returns a hashmap pointer
* @param size: Indicates the initial size of the map.
* @param compare: Pointer to the compare function.
* @param load_factor: Sets the maximum load factor.
*/
HashMap *hash_map_create(size_t size, HashCmp compare, const float load_factor);

/*Deallocate function.
* @param map: Pointer to the HashMap which will be deallocated.
*/
void hash_map_delete(HashMap *map);

/*Return TRUE if the map is empty (it has no association), FALSE otherwise. 
* -1 if map is NULL.
* @param map: Pointer to HashMap.
*/
int hash_map_is_empty(HashMap *map);

/*Return the number of the associations loaded into the map.
* @param map: Pointer to HashMap.
*/
int hash_map_nr_associations(HashMap *map);

/*Delete all associations of the map. Attention, this function 
* does not deallocate the memory associated with associations.
* @param map: Pointer to HashMap.
*/
void hash_map_delete_associations(HashMap *map);

/*Returns TRUE if the specified key is present into the Hash Map, FALSE otherwise.
* @param map: Pointer to HashMap.
* @param key: Pointer to the key.
*/
int hash_map_test_key(HashMap *map, void *key);

/*Arming function. Inserts the <Key, value> association into the map 
* specified by parameter. Return a pointer to the map itself.
* @param map: Pointer to HashMap.
* @param key: Pointer to Key.
* @param value: Pointer to Value.
*/
HashMap *hash_map_insert(HashMap *map, void *key, void *value);

/*Returns pointer to value if the key passed by argument is present into the Hash Map.
* @param map: Pointer to HashMap.
* @param key: Pointer to Key.
*/
void *hash_map_search(HashMap *map, void *key);

/*Delete function. Delete the association corresponding to the key into the map 
* specified by parameter. Return a pointer to the map itself.
* @param map: Pointer to HashMap.
* @param key: Pointer to Key.
*/
HashMap *hash_map_delete_item(HashMap *map, void *key);

/*Returns an array of keys loaded in the map
  @param map HashMap*
*/
void **hash_map_keys_used(HashMap *map);

/*Allocates and return a new hash_map witch contain
* the same associations of the old map passed by arguments.  
* The size of the new map is specified by new_size parameter.
* @param map: Pointer to the old HashMap.
* @param new_size: Indicates the size of the new map.
*/
HashMap *realloc_map(HashMap *map, size_t new_size);

/*Return the size of the map
* @param map: HashMap*
*/
int hash_map_size(HashMap *map);

/*Print size of the map and the number of associations loaded in.
* @param map: HashMap*
*/
void hash_map_status(HashMap *map);

/*Hash function*/
int hash_code(void *key, int size);

/*Support function*/
HashEntry *sup_insert(void *key, void *value);
HashEntry *sup_delete(HashMap *map, HashEntry *head, void *key);
/*****************/

