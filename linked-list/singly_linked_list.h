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
void delete_node(struct list_t *list,void *val_del);
void free_list(struct list_t *list);

#if defined (SINGLY_LINKED_LIST_INIT)
struct list_t *create_list(size_t size, struct operation_t operation){
    struct list_t *list = malloc(sizeof(struct list_t));
    if(!list){
        printf("malloc init error\n");
        exit(-1);
    }
    list->size = size;
    list->operation = operation;
    list->head = NULL;
    return list;
}

struct node_t *create_node(void *val){
    struct node_t *node = malloc(sizeof(struct node_t));
    if(!node){
        printf("malloc init error in node creation\n");
        exit(-1);
    }
    node->val = val;
    node->next = NULL;
    return node;
}
void append_elem_list(struct list_t *list){
    struct node_t *node = create_node(list->operation.input_elem("Enter a value to append: "));
    if(!list->head){
        list->head = node;
        return;
    }
    struct node_t *temp = list->head;
    while(temp->next) temp = temp->next;
    temp->next = node;
}

void print_list(struct list_t *list){
    struct node_t *head = list->head;
    while(head){
        list->operation.print_elem(head->val);
        printf("-->");
        head = head->next;
    }
    printf("NULL\n");
}

struct node_t *find_node(struct list_t *list,void *val){
    struct node_t *head = list->head;
    while(head){
        if(list->operation.compare(head->val,val)==0) return head;
        head = head->next;
    }
    return NULL;
}

void insert_after(struct list_t *list,void *val,void *val_find){
    struct node_t *node = find_node(list,val_find);
    if(!node){
        printf("The value doesn't exisit in the linked list\n");
        return;
    }
    struct node_t *temp = node->next,*new;
    new = create_node(val);
    node->next = new;
    new->next = temp;
}

void delete_node(struct list_t *list, void *val_del){
    struct node_t **pointer= &list->head,*del;
    while(*pointer && list->operation.compare((*pointer)->val,val_del)) pointer = &(*pointer)->next;
    if(!*pointer){
        printf("Value not found\n");
        return;
    }
    del = *pointer;
    *pointer = del->next;
    list->operation.free_elem(del->val);
    free(del);
}

void free_list(struct list_t *list){
    struct node_t *head = list->head;
    while(head){
        struct node_t *rem = head;
        head = head->next;
        list->operation.free_elem(rem->val);
        free(rem);
    }
    free(list);
}
#endif
