#pragma once

#include <stdlib.h>

typedef int (*compare)(void **, int, int);

/*Insertion Sort
* Sorting Alghotims for generic object.
* @param obj: array of pointer witch every pointer points to a single generic object
* @param obj_size: numer of object pointed by obj.
* @param *compare_method: method used to comparing two generic object. Must be specific for the type of the generic object.
*/
int insertion_sort(void **obj, size_t obj_size, compare compare_method);

/*Quick Sort
* Sorting Alghotims for generic object.
* @param obj: array of pointer witch every pointer points to a single generic object
* @param obj_size: numer of object pointed by obj.
* @param *compare_method: method used to comparing two generic object. Must be specific for the type of the generic object.
*/
int quick_sort(void **obj, size_t obj_size, compare compare_method);
void quick_sort_method(void **obj, int begin_pos, int end_pos, compare compare_method);
int quick_sort_partition(void **obj, int pivot, int i, int j, compare compare_method);
