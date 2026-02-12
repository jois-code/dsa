#include <stdio.h>
#include <stdlib.h>

typedef struct List list_t;

typedef struct{
    void (*add)(list_t *l,int x);
    void (*remove)(list_t *l,int index);
}ops_table;

struct List{
    int *list;
    int size;
    ops_table ops;
};

void add(list_t *l,int x);
void del(list_t *l,int index);

const ops_table ops = {
    .add = add,
    .remove = del,
};


int main(){
    list_t list = {.list = malloc(sizeof(int)),.size=0,.ops=ops};
    int choice = 0;
    do{
        printf("Welcome to this menu driven program!!!\n");
        printf("1.Add Elements to the list.\n");
        printf("2.Remove Elements from the list.\n");
        printf("3.Count Elements from the list.\n");
        printf("4.View Elements from the list.\n");
        printf("5.Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        if(choice == 5) break;
        system("clear");
        switch(choice){
            case 1:
                list.ops.add(&list,1);
                break;
            case 2:
                list.ops.remove(&list,list.size-1);
                break;
            case 3:
                printf("The no of elements in the list is %d\n",list.size);
                break;
            case 4:
                for(int i=0;i<list.size;i++)
                    printf("%-4d",list.list[i]);
                printf("\n");
            default:
                printf("Please enter a valid statement\n");
        }
    }while(0==0);
}

void add(list_t *l,int x){
    int size = l->size;
    int *temp = realloc(l->list,(size+1)*sizeof(int));
    if(!temp) return;
    l->list = temp;
    l->list[size] = x;
    l->size++;
}

void del(list_t *l,int index){
    if(l->size==0 || l->size <=index){
        return;
    }
    for(int i=index;i+1<l->size;i++)
        l->list[i] = l->list[i+1];
    l->size--;
}
