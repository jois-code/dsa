// i should have named it dynamic_not_so_generic_array :(
#include "dynamic_array.h"

int main(){
    int ch, opt;
    arr_t *arr;

    printf("Select datatype:\n");
    printf("1.Integer  2.Double  3.Float  4.Character\n>> ");
    if(scanf(" %d",&ch)!=1 || ch<1 || ch>4){
        printf("Invalid choice.\n");
        return -1;
    }
    // clears buffer
    clear_stdin();

    arr = create_array((type_e)(ch-1));
    if(!arr){ printf("Failed to create array.\n"); return -1; }

    while(1){
        printf("\n1.Add  2.Remove  3.Find  4.Print  5.Info  0.Exit\n>> ");
        if(scanf(" %d",&opt)!=1){ clear_stdin(); continue; }
        clear_stdin();

        char buf[sizeof(double)] = {0};
        int idx;

        switch(opt){
            case 1:
                arr->input_elem(buf);
                add_val(arr,buf);
                printf("Value added.\n");
                break;
            case 2:
                if(arr->size==0){ printf("Array is empty. Add a value first.\n"); break; }
                arr->input_elem(buf);
                idx = remove_val(arr,buf);
                if(idx!=-1) printf("Removed at index %d.\n",idx);
                break;
            case 3:
                if(arr->size==0){ printf("Array is empty. Add a value first.\n"); break; }
                arr->input_elem(buf);
                idx = find_val(arr,buf);
                if(idx==-1) printf("Not found.\n");
                else printf("Found at index %d.\n",idx);
                break;
            case 4:
                print_arr(arr);
                break;
            case 5:
                printf("Size: %d | Cap: %d | Elem size: %zu\n",
                        arr->size, arr->cap, arr->elem_size);
                break;
            case 0:
                free_arr(arr);
                return 0;
            default:
                printf("Invalid option.\n");
        }
    }
}

arr_t *create_array(type_e type){
    arr_t *arr = malloc(sizeof(arr_t));
    if (!arr) { printf("malloc error\n"); exit(-1); }

    *arr = (arr_t){.size=0, .cap=2, .type=type};
    switch (type){
        case INT:
            arr->elem_size = sizeof(int);
            arr->print_elem = print_int;
            arr->input_elem = input_int;
            break;
        case FLOAT:
            arr->elem_size = sizeof(float);
            arr->print_elem = print_float;
            arr->input_elem = input_float;
            break;
        case DOUBLE:
            arr->elem_size = sizeof(double);
            arr->print_elem = print_double;
            arr->input_elem = input_double;
            break;
        case CHAR:
            arr->elem_size = sizeof(char);
            arr->print_elem = print_char;
            arr->input_elem = input_char;
            break;
        default: free(arr); return NULL;
    }

    arr->arr = malloc(arr->elem_size * 2);
    if (!arr->arr){
        printf("malloc error\n");
        exit(-1);
    }
    return arr;
}

void print_arr(arr_t *arr){
    if(arr->size==0){
        printf("Dynamic Array is empty :( Please add a value\n");
        return;
    } for(int i = 0;i<arr->size;i++) arr->print_elem((char*)arr->arr+(i*arr->elem_size)); printf("\n"); }
int add_val(arr_t *arr,void *val){
    if(arr->size == arr->cap){
        arr->cap *= 2;
        void *temp = realloc(arr->arr,arr->elem_size*arr->cap);
        if(!temp){
            printf("realloc error\n");
            exit(-1);
        }
        arr->arr = temp;
    }
    memcpy(((char*)(arr->arr))+(arr->size*arr->elem_size),val,arr->elem_size);
    arr->size++;
    return 0;
}
int find_val(arr_t *arr,void *val){
    for(int i=0;i<arr->size;i++)
        if(memcmp(((char*)arr->arr)+i*arr->elem_size,val,arr->elem_size)==0) return i;
    return -1;
}
int remove_val(arr_t *arr,void *val){
    int index = find_val(arr,val);
    if(index==-1){
        printf("Array element is not present\n");
        return -1;
    }
    for(int i=index;i<arr->size-1;i++)
        memcpy((char*)arr->arr+i*arr->elem_size,(char*)arr->arr+(i+1)*arr->elem_size,arr->elem_size);
    arr->size--;
    return index;
}

void print_int(void *p){printf("%d\t",*(int*)p);}
void print_float(void *p){printf("%.4f\t",*(float*)p);}
void print_double(void *p){printf("%.4lf\t",*(double*)p);}
void print_char(void *p){printf("%c\t",*(char*)p);}

void input_int(void *p){
    printf("Enter an integer: ");
    if(scanf(" %d",(int*)p)<1){
        printf("Enter a valid input\n");
        exit(-1);
    }
}

void input_float(void *p){
    printf("Enter a float: ");
    if(scanf(" %f",(float*)p)<1){
        printf("Enter a valid input\n");
        exit(-1);
    }
}

void input_double(void *p){
    printf("Enter a double: ");
    if(scanf(" %lf",(double*)p)<1){
        printf("Enter a valid input\n");
        exit(-1);
    }
}

void input_char(void *p){
    printf("Enter a character: ");
    if(scanf(" %c",(char*)p)<1){
        printf("Enter a valid input\n");
        exit(-1);
    }
}

void free_arr(arr_t *arr){
    free(arr->arr);
    free(arr);
}

void clear_stdin(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
