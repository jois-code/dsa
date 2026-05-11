#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_t{
    struct node_t *next;
    void *val;
};

struct operation_t{
    void *(*input_elem)(char *);
    void (*print_elem)(void*);
    int (*compare)(void *, void *);
    void (*free_elem)(void *);
};

struct list_t{
    struct node_t *head;
    size_t size;
    struct operation_t operation;
};

struct list_t *create_list(size_t size,struct operation_t operation);
struct node_t *create_node(void *val);
void print_list(struct list_t *list);
void append_elem_list(struct list_t *list);
struct node_t *find_node(struct list_t *list,void *val);
void insert_after(struct list_t *list,void *val,void *val_find);
void free_list(struct list_t *list);
