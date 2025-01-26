#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

#define MAX_OP_LEN 100

char* getop(char*);
void push(double);
void duplicate();
double pop();

typedef struct stack {
    double data;
    struct stack* next;
} stack_t;

stack_t *head = NULL;

int main(int argc, char *argv[]) 
{
    char* op = malloc(sizeof(char) * MAX_OP_LEN);
    char* num = malloc(sizeof(char) * MAX_OP_LEN);
    double tmp;
    double tmp2;

    printf("\tReverse Polish Notation Calculator\n\n");
    printf("This is a calculator written in C that uses Reverse Polish Notation (RPN)\n");
    printf("RPN is where you specify the operands first then the operator after, so 5+9 would become 5 9 +\n");
    printf("This removes the need for the order of operations and parenthesis to be built into the calculator\n");
    printf("Type help or h for a list of commands\n\n");

    while ((op = getop(num))) {
        if (strcmp(op, "0") == 0) {
            push(atof(num));
        } else if (strcmp(op, "+") == 0) {
            push(pop() + pop());
        } else if (strcmp(op, "-") == 0) {
            tmp = pop();
            push(pop() - tmp);
        } else if (strcmp(op, "*") == 0) {
            push(pop() * pop());
        } else if (strcmp(op, "/") == 0) {
            tmp = pop();
            if (tmp == 0) {
                fprintf(stderr, "Error: Division by zero\n");
            } else {
                push(pop() / tmp);
            }
        } else if (strcmp(op, "%") == 0) {
            tmp = pop();
            if (tmp == 0) {
                fprintf(stderr, "Error: Division by zero\n");
            } else {
                push(remainder(pop(), tmp));
            }
        } else if (strcmp(op, "^") == 0 || strcmp(op, "pow") == 0) {
            push(pow(pop(), pop()));
        } else if (strcmp(op, "exp") == 0) {
            push(exp(pop()));
        } else if (strcmp(op, "sin") == 0) {
            push(sin(pop()));
        } else if (strcmp(op, "cos") == 0) {
            push(cos(pop()));
        } else if (strcmp(op, "pi") == 0) {
            push(M_PI);
        } else if (strcmp(op, "s") == 0 || strcmp(op, "swap") == 0) {
            tmp = pop();
            tmp2 = pop();
            push(tmp);
            push(tmp2); 
        } else if (strcmp(op, "d") == 0 || strcmp(op, "dupe") == 0 || strcmp(op, "duplicate") == 0) {
            duplicate();
        } else if (strcmp(op, "c") == 0 || strcmp(op, "clear") == 0) {
            while (head != NULL) {
                pop();
            }
        } else if (strcmp(op, "h") == 0 || strcmp(op, "help") == 0) {
            printf("\tCommands\n\n");
            printf("+ : addition\t\t\t\t\t- : subtraction\n* : multiplication\t\t\t\t/ : division\n%% : modulation\n^ or pow : exponent\t\t\t\t");
            printf("e or exp : natural exponent\nsin : sine\t\t\t\t\tcos : cosine\npi : pi operand\ns or swap : swaps most recent operands\nd or duplicate : dupes most recent operand\nc or clear : clears the stack\t\t\th or help : shows this menu\n");
            printf("\nType any number to add it to the stack -->");
        } else {
            fprintf(stderr, "Error: Unrecognized command %s\n", op);
        }

        printf("\t[");
        stack_t *temp=head;
        while(temp!=NULL)
        {
            printf(" %0.8g", temp->data);
            temp=temp->next;
        }
        printf(" ]\n");
    }
}

char* getop(char* n) 
{
    int c, i;

    int lim = MAX_OP_LEN;

    i = 0;
    while (--lim > 0 && (c=getchar()) != '\n') {
        n[i++] = c;
    }
    n[i] = '\0';

    if (n[1] == '\0' && n[0] == '-') {
        return "-";
    }

    for (int o=0; n[o] != '\0'; o++) {
        if (!isdigit(n[o]) && n[o] != '.' && n[o] != '-') {
            return n;
        }
    }
    return "0";
}

void push(double data)
{
    if (head == NULL) {
        head = (stack_t *) malloc(sizeof(stack_t));
        if (head == NULL) {
            fprintf(stderr, "Error: Could not malloc\n");
            return;
        }
        head->data = data;
        head->next = NULL;
        return;
    }

    stack_t *current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = (stack_t *) malloc(sizeof(stack_t));
    if (current->next == NULL) {
        fprintf(stderr, "Error: Could not malloc\n");
        return;
    }

    current->next->data = data;
    current->next->next = NULL;
}

void duplicate()
{
    if (head == NULL) {
        fprintf(stderr, "Error: Cannot duplicate, stack empty");
    }

    stack_t *current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = (stack_t *) malloc(sizeof(stack_t));
    if (current->next == NULL) {
        fprintf(stderr, "Error: Could not malloc\n");
    }

    current->next->data = current->data;
    current->next->next = NULL;
}

double pop()
{
    double popData;

    if (head == NULL) {
        fprintf(stderr, "Error: Could not pop, stack emtpy\n");
        return 1.0;
    }

    if (head->next == NULL) {
        popData = head->data;
        free(head);
        head = NULL;
        return popData;
    }

    stack_t *current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    popData = current->next->data;
    free(current->next);
    current->next = NULL;
    return popData;
}
