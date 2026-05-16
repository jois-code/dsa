#define STACK_INIT
#include "stack.h"

int is_match(char open, char close){
    return (open == '{' && close == '}') ||
           (open == '(' && close == ')') ||
           (open == '[' && close == ']');
}

int compare(void *a, void *b){
    char *x = (char *)a;
    char *y = (char *)b;
    return *x - *y;
}

int bracket(struct stack *st, char *ch){
    char c = *ch;
    if (c == '\0') return st->size == 0 ? 0 : 1;

    switch (c){
        case '{':
        case '(':
        case '[':
            push_val(st, &c);
            break;

        case '}':
        case ')':
        case ']':{
            void *top = peek(st);        /* direct pointer — no alloc */
            if (!top) return -1;
            char open = *(char *)top;
            if (!is_match(open, c)) return -1;
            free(pop(st));               /* free the pop'd copy */
            break;
        }
    }
    return bracket(st, ch + 1);
}

int main(){
    char ch[1024];
    struct stack *st;
    scanf("%[^\n]", ch);
    st = create_stack(sizeof(char), (struct operation_t){.compare = compare});
    printf("%d\n", bracket(st, ch));
    free_stack(st);
    return 0;
}
