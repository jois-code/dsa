#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Type{
    INT, DOUBLE, FLOAT,CHAR
}type_e;

typedef struct Array arr_t;
struct Array{
    int size,cap;
    type_e type;
    void *arr;
    size_t elem_size;
    void (*print_elem)(void*);
    void (*input_elem)(void *);
};

arr_t *create_array(type_e type);
int add_val(arr_t *arr,void *val);
int remove_val(arr_t *arr,void *val);
int find_val(arr_t *arr,void *val);
void print_arr(arr_t *arr);
void free_arr(arr_t *arr);

// print
void print_int(void *p);
void print_double(void *p);
void print_float(void *p);
void print_char(void *p);

//input
void input_int(void *p);
void input_float(void *p);
void input_double(void *p);
void input_char(void *p);

void clear_stdin(void);
