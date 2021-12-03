#include <stdlib.h>
#include <stdio.h>

typedef struct _Record Record;
typedef int (*record_field_compare)(int, void**, int, int, int, int);

/*struttura da utilizzare ps. non mettiamo un puntatore a funzione sarebbe furviante, la teniamo fuori il compare*/
struct _Record {
  int id;
  char* field1;
  int   field2;
  float field3;
}

/*questa funzione scambia due puntatori di tipo generico in posizione a e b, partendo dal doppio puntatore
che punterà alla posizione zero*/
void swap(void** obj, int a, int b) {
  void* temp = *(obj+a);
  *(obj+a) = *(obj+b);
  *(obj+b) = temp;
}

static float compare(int mode, void** obj, int a, int i, int b, int j) {
  switch(mode) {
    case 0:
      return *((int *)*(obj+a)+i) - *((int *)*(obj+b)+j);
    break;

    case 1:
      return *((char *)*(obj+a)+i) - *((char *)*(obj+b)+j);
    break;

    case 2:
      return *((float *)*(obj+a)+i) - *((float *)*(obj+b)+j);
    break;

    default:
    exit(0);
    break;
  }
}


void insertion_sort(void** obj, size_t obj_size, record_field_compare compare, int mode) {
  for(int i=0; i<obj_size; i++) {
    int j = i;
      while(j>0) {
			  if(compare(mode, obj, j, mode, i, mode)>0) {
				  swap(obj, i, j);
        }
          j--;
      }
    }
} 
*/

int main() {
  int size = 10;

  void** a = malloc(sizeof(void *) * size);

  int* array = malloc(sizeof(int) * size);
  
  char* array1 = malloc(sizeof(char) * size);

  float* array2 = malloc(sizeof(float) * size);

  for(int i=0; i<size; i++) {
    *(array+i) = i;
    *(array1+i) = 'a'+i;
    *(array2+i) = (float)i/5;
  }

    for(int i=0; i<size; i++)
    printf("%d ", *(array+i));
    printf("\n");
    for(int i=0; i<size; i++)
    printf("%c ", *(array1+i));
    printf("\n");
    for(int i=0; i<size; i++)
    printf("%f ", *(array2+i));

  
  *(a) = (void *) array;
  *(a+1) = (void *) array1;
  *(a+2) = (void *) array2;

  printf("\n\n");
  
  printf("indirizzo di *a = %d, indirizzo di array = %d", *a, array);
  printf("\n");
  printf("indirizzo di *a = %d, indirizzo di array = %d", *(a+1), array1);
  printf("\n");
  printf("indirizzo di *a = %d, indirizzo di array = %d", *(a+2), array2);

  printf("\n\n");

  for(int i=0; i<size; i++)
    printf("%d ", *((int *)*(a)+i));
  printf("\n");
  for(int i=0; i<size; i++)
    printf("%c ", *((char *)*(a+1)+i));
  printf("\n");  
  for(int i=0; i<size; i++)
    printf("%f ", *((float *)*(a+2)+i));

  swap(a, 0, 1);
  swap(a, 1, 2);

  
  printf("\n\n");
  printf("after swapping"); 
  printf("\n\n");
  

  for(int i=0; i<size; i++)
    printf("%c ", *((char *)*(a)+i));
    printf("\n");
  for(int i=0; i<size; i++)
    printf("%f ", *((float *)*(a+1)+i));
    printf("\n");
  for(int i=0; i<size; i++)
    printf("%d ", *((int *)*(a+2)+i));

  printf("\n\n");
  printf("testing comparing..."); 
  printf("\n\n");

  printf("comparing %c with %c...\nresult = %f\n\n", *((char *)*(a+0)+4), *((char *)*(a+0)+7), compare(1, a, 0, 4, 0, 7));
  printf("comparing %c with %c...\nresult = %f\n\n", *((char *)*(a+0)+4), *((char *)*(a+0)+7), compare(1, a, 0, 4, 0, 7));
  printf("comparing %c with %c...\nresult = %f\n\n", *((char *)*(a+0)+4), *((char *)*(a+0)+7), compare(1, a, 0, 4, 0, 7));
 
  printf("comparing %f with %f...\nresult = %f\n\n", *((float *)*(a+1)+4), *((float *)*(a+1)+7), compare(2, a, 1, 4, 1, 7));
  printf("comparing %f with %f...\nresult = %f\n\n", *((float *)*(a+1)+4), *((float *)*(a+1)+7), compare(2, a, 1, 4, 1, 7));
  printf("comparing %f with %f...\nresult = %f\n\n", *((float *)*(a+1)+4), *((float *)*(a+1)+7), compare(2, a, 1, 4, 1, 7));
 
  printf("comparing %d with %d...\nresult = %f\n\n", *((int *)*(a+2)+9), *((int *)*(a+2)+0), compare(0, a, 2, 9, 2, 0));
  printf("comparing %d with %d...\nresult = %f\n\n", *((int *)*(a+2)+0), *((int *)*(a+2)+9), compare(0, a, 2, 0, 2, 9));
  printf("comparing %d with %d...\nresult = %f\n\n", *((int *)*(a+2)+4), *((int *)*(a+2)+7), compare(0, a, 2, 4, 2, 7));
 


  /*
  for(int i=0; i<1000000; i++) {
    printf("%d,",*(array+i));
  }
  
  insertion_sort(array, 1000000, compare_int);
  printf("\n");
  
  for(int i=0; i<1000000; i++) {
    printf("%d,",*(array+i));
  }
  */
}