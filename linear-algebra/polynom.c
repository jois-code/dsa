#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct Poly poly_t;

struct Poly {
    double power,coeff;
    poly_t *next;
};

void printPoly(const poly_t *head){
    if (!head){
        printf("0\n");
        return;
    }

    const poly_t *curr = head;
    int first = 1;

    while (curr){
        if (curr->coeff != 0){
            if (!first) printf(curr->coeff > 0 ? " + " : " - ");
            else if (curr->coeff < 0) printf("-");

            double c = fabs(curr->coeff);

            if (curr->power == 0) printf("%.2f", c);
            else if (curr->power == 1) printf("%.2fx", c);
            else printf("%.2fx^%.0f", c, curr->power);
            first = 0;
        }
        curr = curr->next;
    }
    printf("\n");
}

int main(){
    int size;
    poly_t *head = NULL, *temp,*node;
    printf("Enter the A,B and C values where Ax^2 + Bx + C: ");
    for(int i=2;i>=0;i--){
        node = malloc(sizeof(poly_t));
        scanf(" %lf",&node->coeff);
        node->power = i;
        node->next = NULL;
        if(head==NULL){
            head = node;
            temp = node;
        }else{
            temp->next = node;
            temp = node;
        }
    }
    temp = NULL;
    printPoly(head);
}
