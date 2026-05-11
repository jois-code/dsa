#include "singly_linked_list.h"

typedef struct{
    char name[50];
    int age;
    float gpa;
}student_t;

void *input_student_elem(char *msg){
    student_t *s = malloc(sizeof(student_t));
    if (!s){
        printf("Malloc init error\n");
        exit(-1);
    }
    printf("%s\n", msg);
    printf("Name: "); scanf(" %49s", s->name);
    printf("Age: ");  scanf(" %d", &s->age);
    printf("GPA: ");  scanf(" %f", &s->gpa);
    return s;
}

void print_student_elem(void *val){
    student_t *s = (student_t *)val;
    printf("[%s | Age: %d | GPA: %.2f]", s->name, s->age, s->gpa);
}

int compare_student(void *a, void *b){
    student_t *s1 = (student_t *)a;
    student_t *s2 = (student_t *)b;
    return strcmp(s1->name, s2->name);
}

void free_student(void *a){
    free(a);
}

int main(){
    struct operation_t operation = {input_student_elem, print_student_elem, compare_student, free_student};
    struct list_t *list = create_list(sizeof(student_t), operation);

    append_elem_list(list);
    append_elem_list(list);
    append_elem_list(list);

    student_t key = {"Jois", 20, 9.9}; // day dreaming 😭
    struct node_t *node = find_node(list, &key);
    if (node == NULL)
        printf("Student not found\n");
    else
        print_student_elem(node->val);

    printf("\n");
    print_list(list);
    free_list(list);
}

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
