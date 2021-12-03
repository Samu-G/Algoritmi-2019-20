#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
int cmp(int* a,int* b){
return *a - *b;
}
int* int_new(int n) {
    int* result = (int*) malloc(sizeof(int));
    *result = n;

    return result;
}
void utility_create_arrey_zero_size(){
    Data* d=data_create(/*(Data_cmp) cmp,*/0);
}
void utility_insert_object_in_pos_negative(){
    Data* d=data_create(/*(Data_cmp)cmp,*/1);
    int* sup = (int*) malloc(sizeof(int));
    *sup=42;
    data_insert_obj(d,sup,0);
    printf("test lettura array:%d\n",*(int *)data_get(d,-1));
    free(sup);
    data_free(d);    
}

void utility_insert_object_in_generic_position(){
    int max=5;
    Data* d=data_create(/*(Data_cmp)cmp,*/5);
    for ( int i = 0; i < max; i++)
    { 
    data_insert_obj(d,int_new(i),i); }

    for ( int i = 0; i < max; printf("test lettura array:%d\n",*(int *)data_get(d,i)) , i++);
    data_free(d);    
}

void utility_swap_generic(){
    Data* d=data_create(/*(Data_cmp)cmp,*/2);
    puts("array before the swap:");
    for ( int i = 0; i < 2; i++)
    { 
    data_insert_obj(d,int_new(i),i); }
    for ( int i = 0; i < 2; printf("test lettura array:%2d\n",*(int *)data_get(d,i)) , i++);
    puts("array after the swap:\n");
    data_swap(d,0,1);
    for ( int i = 0; i < 2; printf("test lettura array:%2d\n",*(int *)data_get(d,i)) , i++);
    free(d);
}

void first_use_insert_sort(){
    Data* d=data_create(3);
    puts("array before the insert sort:\n");
      data_insert_obj(d,int_new(3),0);
      data_insert_obj(d,int_new(2),1);
      data_insert_obj(d,int_new(1),2); 
    for ( int i = 0; i < 3; printf("test lettura array:%2d\n",*(int *)data_get(d,i)) , i++); 
    data_insert_sort(d,cmp);
    puts("test after insert sort:\n");
    for ( int i = 0; i < 3; printf("test lettura array:%2d\n",*(int *)data_get(d,i)) , i++);
    free(d);
}

void insert_sort_with_array_null(){
    Data *d=data_create(0);
    data_insert_sort(d,cmp);    
}
void insert_sort_with_array_already_ordoned(){
    int *vet=(int*) malloc(sizeof(int)*3);
    for(int i=0;i<3;vet[i]=3-i,i++);
    for(int i=0;i<3;printf("%d\n",vet[i]),i++);
    free(vet);
}
int main(){

//utility_create_arrey_zero_size();

//utility_insert_object_in_pos_negative();

//utility_insert_object_in_generic_position();

//utility_swap_generic();

//insert_sort_with_array_null();

insert_sort_with_array_already_ordoned();

first_use_insert_sort();

}
