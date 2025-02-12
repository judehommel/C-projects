#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 5000
#define HEAP_SIZE 30000

typedef struct loop {
    int val;
    struct loop *next;
} stack;

stack *head = NULL;

void push(int x);
int pop();
int gettop();

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Error: input a brainfuck file to run\n");
        return 1;
    } else if (argc > 2) {
        fprintf(stderr, "Error: Only input one argument\n");
        return 1;
    }

    int *ptr = (int*)malloc(sizeof(int) * HEAP_SIZE);
    if (ptr == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for heap\n");
        return 1;
    }

    for (int i=0; i<HEAP_SIZE; i++) {
        ptr[i] = 0;
    }

    FILE *fptr;

    // Open a file in read mode
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        fprintf(stderr, "Error: Could not open file\n");
        return 1;
    }

    char *code = (char*)malloc(sizeof(char) * MAX_CHARS);
    if (code == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for code\n");
        fclose(fptr);
        return 1;
    }
    
    char *buf = (char*)malloc(sizeof(char) * MAX_CHARS);
    if (buf == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for buf\n");
        fclose(fptr);
        return 1;
    }

    int counter = 0;
    // Read file into code
    while ((*code = fgetc(fptr)) != EOF) {
        code++;
        counter++;
    }
    while (counter != 0) {
        code--;
        counter--;
    }

    int tmp = 0;
    for (int i=0; code[i] != '\0'; i++) {
        switch (code[i]) {
            case '+':
                (*ptr)++;
                break;
            case '-':
                (*ptr)--;
                break;
            case '<':
                ptr--;
                break;
            case '>':
                ptr++;
                break;
            case '.':
                printf("%c", *ptr);
                break;
            case ',':
                *ptr = getchar();
                break;
            case '[':
                push(i);
                if (*ptr == 0) {
                    while (code[i] != ']' && tmp != 0) {
                        if (code[i] == '\0') {
                            fprintf(stderr, "Error: Missmatched Bracket");
                            return 1;
                        }
                        if (code[i] == '[') {
                            tmp++;
                        }
                        if (code[i] == ']') {
                            tmp--;
                        }
                        i++;
                    }
                }
                break;
            case ']':
                if (*ptr == 0) {
                    pop();
                } else {
                    i = gettop(); 
                }
                break;
        }
    }

    free(code);
    fclose(fptr);

    return 0;
}

void push(int x)
{
    if (head == NULL) {
        head = (stack*)malloc(sizeof(stack));
        if (head == NULL) {
            fprintf(stderr, "Error: Could not malloc\n");
            return;
        }
        head->val = x;
        head->next = NULL;
        return;
    } 

    stack *current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = (stack*)malloc(sizeof(stack));
    if (current->next == NULL) {
        fprintf(stderr, "Error: Could not malloc\n");
        return;
    }
    current->next->val = x;
    current->next->next = NULL;
    return;
}

int pop() 
{
    int retVal;
    if (head == NULL) {
        fprintf(stderr, "Error: Missmatched Bracket\n");
        return 0;
    }

    if (head->next == NULL) {
        retVal = head->val;
        free(head);
        head = NULL;
        return retVal;
    }

    stack *current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    retVal = current->val;
    free(current->next);
    current->next = NULL;
    return retVal;
}

int gettop()
{
    if (head == NULL) {
        fprintf(stderr, "Error: Missmatched Bracket\n");
        return 0;
    }

    stack *current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    return current->val;
}
