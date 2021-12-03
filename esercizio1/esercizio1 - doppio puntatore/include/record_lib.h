#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE_FIELD1 1024

/*Definition of the data structure Record*/
typedef struct _Record
{
  int id;
  char *field1;
  int field2;
  float field3;
} Record;

/*Return a pointer to Records, n_of_records specific the amount of memory needed to be allocated.*/
Record *record_new(int n_of_records);

/*Free memory of the pointer to Records r.*/
void record_remove(Record *r);

/*Set the record field at position specified by the index.*/
void record_insert(Record *r, int id, char *field1, int field2, float field3);

/*Compare function for string in field1.*/
int record_string_cmp(void **obj, int a, int b);

/*Compare function for integer in field2.*/
int record_int_cmp(void **obj, int a, int b);

/*Compare function for string in field3.*/
int record_float_cmp(void **obj, int a, int b);

/*Generic function. Rows_count count the number of rows in the file specified in file_name. 
* In case of unsuccesful opening, return -1
*/
int rows_count(const char *file_name);

/*Load the data in a Record* in the file specified by file_name.
* Warning: For a correct use of this function the file must have this skeleton: 
* (int) mandatory in ascending order, followed by a comma, (string),
* followed by a comma, (int), followed by a comma, (float).
*/
Record *record_load_file(const char *file_name, int *_nr_lines);

/*Printing function*/
void record_print(Record *r, int size);
