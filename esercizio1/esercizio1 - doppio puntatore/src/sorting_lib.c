#include "sorting_lib.h"

int insertion_sort(void **obj, size_t obj_size, compare compare_method)
{
  if (obj_size <= 0 || obj == NULL)
  {
    return -1;
  }
  else
  {
    void *temp;
    for (int i = 1; i < obj_size; i++)
    {
      int j = i;
      while (j > 0 && compare_method(obj, j - 1, j) > 0)
      {
        temp = obj[j - 1];
        obj[j - 1] = obj[j];
        obj[j] = temp;
        j--;
      }
    }
    return 1;
  }
}

int quick_sort_partition(void **obj, int pivot, int i, int j, compare compare_method)
{
  int begin = i + 1, end = j;
  void *temp;
  while (begin <= end)
  {
    if (compare_method(obj, begin, pivot) <= 0)
    {
      begin = begin + 1;
    }
    else if (compare_method(obj, end, pivot) > 0)
    {
      end = end - 1;
    }
    else
    {
      temp = obj[begin];
      obj[begin] = obj[end];
      obj[end] = temp;
      begin = begin + 1;
      end = end - 1;
    }
  }
  temp = obj[pivot];
  obj[pivot] = obj[end];
  obj[end] = temp;
  return end;
}

void quick_sort_method(void **obj, int begin_pos, int end_pos, compare compare_method)
{
  if (end_pos > 1)
  {
    int pivot = quick_sort_partition(obj, begin_pos, begin_pos, end_pos, compare_method);
    if ((pivot - begin_pos) >= 2)
    {
      quick_sort_method(obj, begin_pos, pivot - 1, compare_method);
    }
    if ((end_pos - pivot) >= 2)
    {
      quick_sort_method(obj, pivot + 1, end_pos, compare_method);
    }
  }
}

int quick_sort(void **obj, size_t obj_size, compare compare_method)
{
  if (obj == NULL || obj_size == 0)
  {
    return -1;
  }
  else
  {
    int begin_pos = 0, end_pos = obj_size - 1;
    quick_sort_method(obj, begin_pos, end_pos, compare_method);
    return 1;
  }
}