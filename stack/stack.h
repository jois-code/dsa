#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct operation_t{
    void *(*input_elem)(char *);
    void (*print_elem)(void *);
    int (*compare)(void *, void *);
    void (*free_elem)(void *);
};

struct stack{
    void *val;
    size_t size, cap;
    size_t elem_size;
    struct operation_t operation;
};

struct stack *create_stack(size_t size, struct operation_t operation);
void push(struct stack *st);
void push_val(struct stack *st, void *val);
void *pop(struct stack *st);
void *peek(struct stack *st);
void *search(struct stack *st, void *val);
void free_stack(struct stack *st);

#if defined(STACK_INIT)

struct stack *create_stack(size_t size, struct operation_t op){
    struct stack *st = malloc(sizeof(struct stack));
    if (!st){
        fprintf(stderr, "malloc init error\n");
        exit(EXIT_FAILURE);
    }
    st->operation = op;
    st->elem_size = size;
    st->cap = 2;
    st->size = 0;
    st->val = malloc(size * st->cap);
    if (!st->val){
        fprintf(stderr, "malloc init error\n");
        exit(EXIT_FAILURE);
    }
    return st;
}

static void resize(struct stack *st, size_t new_cap){
    void *temp = realloc(st->val, new_cap * st->elem_size);
    if (!temp){
        fprintf(stderr, "realloc error\n");
        exit(EXIT_FAILURE);
    }
    st->val = temp;
    st->cap = new_cap;
}

void push_val(struct stack *st, void *val){
    if (st->size == st->cap)
        resize(st, st->cap * 2);
    memcpy((char *)st->val + (st->size * st->elem_size), val, st->elem_size);
    st->size++;
}

void push(struct stack *st){
    void *val = st->operation.input_elem("Enter an element to push: ");
    push_val(st, val);
}

void *pop(struct stack *st){
    if (st->size == 0) return NULL;
    void *val = malloc(st->elem_size);
    if (!val) { fprintf(stderr, "malloc error\n"); exit(EXIT_FAILURE); }
    st->size--;
    memcpy(val, (char *)st->val + (st->size * st->elem_size), st->elem_size);
    if (st->size > 0 && st->size == st->cap / 4)
        resize(st, st->cap / 2);
    return val;
}

void *peek(struct stack *st){
    if (st->size == 0) return NULL;
    return (char *)st->val + ((st->size - 1) * st->elem_size);
}

void *search(struct stack *st, void *val){
    size_t index = st->size;
    void *temp = malloc(st->elem_size);
    if (!temp) { fprintf(stderr, "malloc error\n"); exit(EXIT_FAILURE); }
    while (index > 0){
        memcpy(temp, (char *)st->val + ((index - 1) * st->elem_size), st->elem_size);
        if (st->operation.compare(val, temp) == 0) return temp;
        index--;
    }
    free(temp);
    return NULL;
}

void free_stack(struct stack *st){
    free(st->val);
    free(st);
}

#endif
