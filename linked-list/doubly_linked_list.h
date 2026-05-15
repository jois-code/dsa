#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_t{
    struct node_t *next,*prev;
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
struct node_t *find_node(struct list_t *list,void *val);
void append_elem_list(struct list_t *list);
void insert_after(struct list_t *list,void *val,void *val_find);
void delete_node(struct list_t *list,void *val_del);
void free_list(struct list_t *list);
void print_list(struct list_t *list);

#if defined (DOUBLY_LINKED_LIST_INIT)
struct list_t *create_list(size_t size,struct operation_t operation){
    struct list_t *list = malloc(sizeof(struct list_t));
    if(!list){
        fprintf(stderr,"malloc init failed\n");
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
        fprintf(stderr,"malloc init failed\n");
        exit(-1);
    }
    node->next = NULL;
    node->prev = NULL;
    node->val = val;
    return node;
}

struct node_t *find_node(struct list_t *list,void *val){
    struct node_t *head = list->head;
    while(head){
        if(list->operation.compare(head->val,val)==0) return head;
        head = head->next;
    }
    return NULL;
}

void append_elem_list(struct list_t *list){
    struct node_t *node = create_node(list->operation.input_elem("Enter an element to append: ")),*temp;
    if(!list->head){
        node->prev = NULL;
        list->head = node;
        return;
    }
    temp = list->head;
    while(temp->next){
        temp = temp->next;
    }
    node->prev = temp;
    temp->next = node;
}

void insert_after(struct list_t *list,void *val,void *val_find){
    struct node_t *node = find_node(list,val_find);
    if(!node){
        fprintf(stderr,"The value doesn't exisit in the linked list\n");
        return;
    }
    struct node_t *temp = create_node(val);
    temp->prev = node;
    temp->next = node->next;
    if(temp->next) temp->next->prev = temp;
    node->next = temp;
}

void delete_node(struct list_t *list,void *val_del){
    struct node_t *prev,*node;
    node = find_node(list,val_del);
    if(!node){
        fprintf(stderr,"The value doesn't exisit in the linked list\n");
        return;
    }
    prev = node->prev;
    if(!prev) list->head = node->next;
    else prev->next = node->next;
    if(node->next) node->next->prev = prev;
    list->operation.free_elem(node->val);
    free(node);
}

void free_list(struct list_t *list){
    struct node_t *node,*temp;
    node = list->head;
    while(node){
        temp = node;
        node = node->next;
        list->operation.free_elem(temp->val);
        free(temp);
    }
    free(list);
}

void print_list(struct list_t *list){
    struct node_t *head = list->head;
    printf("NULL<-->");
    while(head){
        list->operation.print_elem(head->val);
        printf("<-->");
        head = head->next;
    }
    printf("NULL\n");
}
#endif
