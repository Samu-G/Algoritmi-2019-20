#include "../include/sorting_lib.h"
#include "../include/record_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void insertion_sort_test_su_record(int selector, int print)
{
  clock_t start_t, end_t;
  char path_name[20];
  int n_of_record;

  printf("\nPlease enter path containing the records to be sorted: ");
  scanf("%s", path_name);
  printf("\n");

  Record *rr = record_load_file(path_name, &n_of_record);

  printf("readed | %d | records\n", n_of_record);

  switch (selector)
  {
  case 1:
    printf("\nSorting on integers ...\n");
    start_t = clock();

    insertion_sort((void *)rr, n_of_record, record_swap, record_int_cmp);

    end_t = clock();
    printf("\nInteger sorting completed. Time spent:%f seconds\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    break;

  case 2:
    printf("\nSorting on floats ...\n");
    start_t = clock();

    insertion_sort((void *)rr, n_of_record, record_swap, record_float_cmp);

    end_t = clock();
    printf("\nFloat sorting completed. Time spent:%f seconds\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    break;

  case 3:
    printf("\nSorting on strings ...\n");
    start_t = clock();

    insertion_sort((void *)rr, n_of_record, record_swap, record_string_cmp);

    end_t = clock();
    printf("\nString sorting completed. Time spent:%f seconds\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    break;

  default:
    exit(1);
    break;
  }

  if (print == 1)
    record_print(rr, n_of_record);

  printf("-----------------------------------------------------------------------------------\n");

  record_remove(rr);
}

void quick_sort_test_su_record(int selector, int print)
{
  clock_t start_t, end_t;
  char path_name[20];
  int n_of_record;

  printf("\nPlease enter path containing the records to be sorted: ");
  scanf("%s", path_name);
  printf("\n");

  Record *rr = record_load_file(path_name, &n_of_record);

  printf("readed | %d | records\n", n_of_record);

  switch (selector)
  {
  case 1:
    printf("\nSorting on integers ...\n");
    start_t = clock();

    quick_sort((void *)rr, n_of_record, record_swap, record_int_cmp);

    end_t = clock();
    printf("\nInteger sorting completed. Time spent:%f seconds\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    break;

  case 2:
    printf("\nSorting on floats ...\n");
    start_t = clock();

    quick_sort((void *)rr, n_of_record, record_swap, record_float_cmp);

    end_t = clock();
    printf("\nFloat sorting completed. Time spent:%f seconds\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    break;

  case 3:
    printf("\nSorting on strings ...\n");
    start_t = clock();

    quick_sort((void *)rr, n_of_record, record_swap, record_string_cmp);

    end_t = clock();
    printf("\nString sorting completed. Time spent:%f seconds\n\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    break;

  default:
    exit(1);
    break;
  }

  if (print == 1)
    record_print(rr, n_of_record);

  printf("-----------------------------------------------------------------------------------\n");

  record_remove(rr);
}

int main()
{
  int selection, selector, print;
  printf("\n\n\n\n||  Sorting test on record  ||\n|| Created by S.G. and M.B. ||\n\n\n\n");

  while (1)
  {
    printf("-----------------------------------------------------------------------------------\n");
    printf("\nInsert 1 for sorting using insertion sort, 2 for sorting with quick sort.\n: ");
    scanf("%d", &selection);
    if (selection == 1)
    {
      printf("Insert 1 for sorting on int, 2 for float, 3 for string.\n: ");
      scanf("%d", &selector);
      printf("do you want to print the ordered records? 1 for YES, 2 for NO.\n: ");
      scanf("%d", &print);
      if (print != 1 && print != 2)
        exit(EXIT_FAILURE);
      switch (selector)
      {
      case 1:
        insertion_sort_test_su_record(selector, print);
        break;
      case 2:
        insertion_sort_test_su_record(selector, print);
        break;
      case 3:
        insertion_sort_test_su_record(selector, print);
        break;
      default:
        exit(1);
      }
    }
    else if (selection == 2)
    {
      printf("Insert 1 for sorting on int, 2 for float, 3 for string.\n: ");
      scanf("%d", &selector);
      printf("do you want to print the ordered records? 1 for YES, 2 for NO.\n: ");
      scanf("%d", &print);
      if (print != 1 && print != 2)
        exit(EXIT_FAILURE);
      switch (selector)
      {
      case 1:
        quick_sort_test_su_record(selector, print);
        break;
      case 2:
        quick_sort_test_su_record(selector, print);
        break;
      case 3:
        quick_sort_test_su_record(selector, print);
        break;
      default:
        exit(1);
      }
    }
    else
      exit(1);
  }
}