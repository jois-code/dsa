#include <stdio.h>
#include <stdlib.h>

typedef struct Node node_t;

struct Node{
    int data;
    node_t *next;
};

int main(){
    node_t *head=NULL, *temp=NULL,*new_node=NULL;
    int size=0;
    printf("Enter the size of the linked list: ");
    scanf("%d",&size);
    printf("Enter %d values: ",size);
    for(int i=0;i<size;i++){
        new_node = malloc(sizeof(node_t));
        scanf("%d",&new_node->data);
        new_node->next = NULL;
        if(head==NULL){
            head = new_node;
            temp = new_node;
        }else{
            temp->next = new_node;
            temp = new_node;
        }
    }
    temp = head;
    while(temp!=NULL){
        printf("%d-->",temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
