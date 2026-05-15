#define DOUBLY_LINKED_LIST_INIT
#include "doubly_linked_list.h"

struct student_t{
    char name[50];
    int age;
    float gpa;
};

void *input_student_elem(char *msg){
    struct student_t *s = malloc(sizeof(struct student_t));
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
    struct student_t *s = (struct student_t *)val;
    printf("[%s | Age: %d | GPA: %.2f]", s->name, s->age, s->gpa);
}

int compare_student(void *a, void *b){
    struct student_t *s1 = (struct student_t *)a;
    struct student_t *s2 = (struct student_t *)b;
    return strcmp(s1->name, s2->name);
}

void free_student(void *a){
    free(a);
}

int main(){
    struct operation_t operation = {input_student_elem, print_student_elem, compare_student, free_student};
    struct list_t *list = create_list(sizeof(struct student_t), operation);

    append_elem_list(list);
    append_elem_list(list);
    append_elem_list(list);

    print_list(list);
    struct student_t key = {"Jois", 20, 9.9}; // still day dreaming 😭
    struct node_t *node = find_node(list, &key);
    if (node == NULL)
        printf("Student not found\n");
    else
        delete_node(list,node->val);

    print_list(list);
    free_list(list);
}
