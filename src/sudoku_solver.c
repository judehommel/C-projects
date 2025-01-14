#include <stdio.h>
#include <math.h>

char inputBoard[9][9];

void printBoard(char inputBoard[9][9], int x, int y);
int bruteForceSolver(char b[9][9]);

int main(int argc, char *argv[]) {
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            inputBoard[i][j] = '-';
        }
    }

    char c;
    char tmp;
    printBoard(inputBoard, 0, 0); 
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            // skip '\n'
            c = getchar();
            while ((tmp = getchar()) != '\n')
                c = tmp;
            // skip rest of input or next line
            if (c == 's' || c == 'n') {
                break;
            } else if (c == 'b') {
                if (j == 0) {
                    i--;
                    j = 8;
                } else {
                    j--;
                }

                if (j == 0) {
                    i--;
                    j = 8;
                } else {
                    j--;
                }
            } else if (c > '9' || c < '0') {
                inputBoard[i][j] = '-';
            } else {
                inputBoard[i][j] = c;
            }
            printBoard(inputBoard, i + floor(j/8.0), (j+1) % 9);
        }
        if (c == 's') {
            break;
        } else if (c == 'n') {
            printBoard(inputBoard, i + 1, 0);
        }
    }

    char board[9][9];
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            board[i][j] = '0';
        }
    }

    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if (inputBoard[i][j] != '-') {
                board[i][j] = inputBoard[i][j];
            }
        }
    }

    if (bruteForceSolver(board)) {
        printBoard(board, -1, -1);
    }

    return 0;
}

int checkHor(char b[9][9], int x, int y)
{
    for (int hor=0; hor<9; hor++) {
        if (hor != x && b[y][x] == b[y][hor]) {
            return 0;
        }
    }
    return 1;
}

int checkVer(char b[9][9], int x, int y)
{
    for (int ver=0; ver<9; ver++) {
        if (ver != y && b[y][x] == b[ver][x]) {
            return 0;
        }
    }
    return 1;
}

int backtrack(char b[9][9], int* x, int* y)
{
    if (*x == 0 && *y == 0) {
        return 0;
    }

    b[*y][*x] = '0';

    if (*x == 0) {
        *y = *y - 1;
        *x = 8;
    } else {
        *x = *x - 1;
    }
    if (b[*y][*x] != inputBoard[*y][*x]) {
        b[*y][*x]++;
        while (!checkHor(b, *x, *y) || !checkVer(b, *x, *y)) {
            if (b[*y][*x] > '9') {
                break;
            }
            b[*y][*x]++;
        }
    }

    if (b[*y][*x] > '9' || !checkVer(b, *x, *y) || !checkHor(b, *x, *y)) {
        return backtrack(b, x, y);
    }
    return 1;
}

int bruteForceSolver(char b[9][9]) 
{
    for (int i=0; i<9; i++) {
        for (int j=0; j<9; j++) {
            if (b[i][j] != inputBoard[i][j]) {
                if (b[i][j] == '0') {
                    b[i][j] = '1';
                }

                while (!checkHor(b, j, i) || !checkVer(b, j, i)) {
                    if (b[i][j] > '9') {
                        break;
                    }
                    b[i][j]++;
                }

                if (b[i][j] > '9' || !checkVer(b, j, i) || !checkHor(b, j, i)) {
                    if (!backtrack(b, &j, &i)) {
                        fprintf(stderr, "Error: Sudoku not solvable\n");
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

#define BOLD  "\e[1m"
#define BDEND "\e[m"
#define GREEN "\033[0;32m" 
#define GREND "\033[0;37m"

void printBoard(char b[9][9], int x, int y) 
{
    printf("\n");

    char* horBoard = "| %c %c %c | %c %c %c | %c %c %c |\n";
    char* boldPos;

    for(int i=0; i<9; i++) {
        if((i) % 3 == 0) {
            printf("+-------+-------+-------+\n");
        }
        for(int j=0; j<9; j++) {
            if(j % 3 == 0) {
                printf("| ");
            }
            if(x == i && y == j) {
                printf(BOLD GREEN "%c " GREND BDEND, b[i][j]);
            } else {
                printf("%c ", b[i][j]);
            }
        }
        printf("|\n");

    }
    printf("+-------+-------+-------+\n");
}

