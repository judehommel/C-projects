#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 4096
#define STACK_SIZE 65536
#define MAX_LOOP_DEPTH 1024

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Error: input a brainfuck file to run\n");
        return 1;
    } else if (argc > 2) {
        fprintf(stderr, "Error: Only input one argument\n");
        return 1;
    }

    int *ptr = (int*)malloc(sizeof(int) * STACK_SIZE);
    int *start = ptr;
    if (ptr == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for heap\n");
        return 1;
    }

    for (int i=0; i<STACK_SIZE; i++) {
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

    // Read file into code
    for (int i=0; (code[i] = fgetc(fptr)) != EOF; i++) {
        ;
    }

    int loops[MAX_LOOP_DEPTH];
    int loopsIndex;
    for (int i=0; code[i] != '\0'; i++) {
        switch (code[i]) {
            case '+':
                if (++*ptr > 127) {
                    *ptr -= 128;
                }
                break;
            case '-':
                if (--*ptr < 0) {
                    *ptr += 128;
                }
                break;
            case '<':
                if (--ptr < start) {
                    ptr += STACK_SIZE;
                }
                break;
            case '>':
                if (++ptr > start + STACK_SIZE) {
                    ptr -= STACK_SIZE;
                }
                break;
            case '.':
                putchar(*ptr);
                break;
            case ',':
                *ptr = getchar();
                break;
            case '[':
                if (*ptr > 0) {
                    loops[loopsIndex++] = i;
                } else {
                    int loop_depth = 1;
                    while (loop_depth > 0) {
                        i++;
                        if (code[i] == '[') loop_depth++;
                        if (code[i] == ']') loop_depth--;
                    }
                }
                break;
            case ']':
                if (*ptr > 0) {
                    i = loops[loopsIndex-1];
                } else if (*ptr <= 0) {
                    loopsIndex--;
                }
                break;
        }
    }

    free(code);
    fclose(fptr);

    return 0;
}

