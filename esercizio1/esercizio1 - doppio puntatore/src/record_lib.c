#include "record_lib.h"

Record *record_new(int n_of_records)
{
  Record *result = (Record *)calloc(n_of_records, sizeof(Record));
  return result;
}

void record_remove(Record *r)
{
  if (r != NULL)
  {
    free(r);
    r = NULL;
  }
}

void record_insert(Record *r, int id, char field1[SIZE_FIELD1], int field2, float field3)
{
  if (r != NULL)
  {
    (r + id)->id = id;
    (r + id)->field1 = strdup(field1);
    (r + id)->field2 = field2;
    (r + id)->field3 = field3;
  }
}

int record_string_cmp(void **obj, int a, int b)
{
  return strcmp(((Record *)obj[a])->field1, ((Record *)obj[b])->field1);
}

int record_int_cmp(void **obj, int a, int b)
{
  if (((Record *)obj[a])->field2 > ((Record *)obj[b])->field2)
    return 1;
  else if (((Record *)obj[a])->field2 < ((Record *)obj[b])->field2)
    return -1;
  else
    return 0;
}

int record_float_cmp(void **obj, int a, int b)
{
  if (((Record *)obj[a])->field3 > ((Record *)obj[b])->field3)
    return 1;
  else if (((Record *)obj[a])->field3 < ((Record *)obj[b])->field3)
    return -1;
  else
    return 0;
}

int rows_count(const char *file_name)
{
  FILE *fp;
  if ((fp = fopen(file_name, "r")) == NULL)
  {
    return -1;
  }
  else
  {
    int nr = 0;
    for (char c = getc(fp); c != EOF; c = getc(fp))
    {
      if (c == '\n')
        nr++;
    }
    fclose(fp);
    return nr;
  }
}

Record *record_load_file(const char *file_name, int *_nr_lines)
{
  Record *data;
  int nr_lines = rows_count(file_name);
  data = record_new(nr_lines);
  *_nr_lines = nr_lines;
  FILE *fp;

  int id;
  char field1[SIZE_FIELD1];
  int field2;
  float field3;

  if ((fp = fopen(file_name, "r")) == NULL)
  {
    printf("\nFile not found.");
    exit(0);
  }

  printf("inserimento dati in corso...\n\n");

  for (size_t i = 0; !feof(fp); i++)
  {
    fscanf(fp, "%d,%1024[^,],%d,%f\n", &id, field1, &field2, &field3);

    record_insert(data, id, field1, field2, field3);
  }

  rewind(fp);
  fclose(fp);

  return data;
}

void record_print(Record *r, int size)
{
  printf("\n\n");
  if (size <= 0)
    exit(1);
  for (int i = 0; i < size; i++)
    printf("%d\t\t%10s\t\t%d\t\t%3.3f\n", (r + i)->id, (r + i)->field1, (r + i)->field2, (r + i)->field3);
}