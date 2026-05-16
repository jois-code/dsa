#define SINGLY_LINKED_LIST_INIT
#include "../linked-list/singly_linked_list.h"

void push_head(struct list_t *list){
    struct node_t *node = create_node(list->operation.input_elem("Enter a integer to push: "));
    node->next = list->head;
    list->head = node;
}

void pop(struct list_t *list){
    struct node_t *temp = list->head;
    if(!temp) return;
    list->head = list->head->next;
    list->operation.free_elem(temp->val);
    free(temp);
}

void *peek(struct list_t *list){
    if(!list->head) return NULL;
    return list->head->val;
}

void *input_elem_int(char *s){
    int *val = malloc(sizeof(int));
    if(!val) {fprintf(stderr,"malloc init error\n");exit(EXIT_FAILURE);}
    printf("%s",s);
    scanf("%d",val);
    return val;
}

void print_elem_int(void *val){
    printf("%d", *(int*)val);
}

int main(){
    struct list_t *list = create_list(sizeof(int),(struct operation_t){.free_elem=free,.input_elem=input_elem_int,.print_elem=print_elem_int});
    push_head(list);
    push_head(list);
    push_head(list);
    push_head(list);
    print_list(list);
    pop(list);
    pop(list);
    print_list(list);
    free_list(list);
}
