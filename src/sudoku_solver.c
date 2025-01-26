#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

char inputBoard[9][9];

void printBoard(char inputBoard[9][9], int x, int y);
int bruteForceSolver(char b[9][9], int x, int y, int storedBacktrack);

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
            // Skip '\n'
            c = getchar();
            while ((tmp = getchar()) != '\n')
                c = tmp;
            // Skip rest of input or next line
            if (c == 's' || c == 'n') {
                break;
            } else if (c == 'b') {
                // Go back 1 iteration 
                if (j == 0) {
                    i--;
                    j = 8;
                } else {
                    j--;
                }
    
                // Do it again 
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

    if (bruteForceSolver(board, 0, 0, 0)) {
        printBoard(board, -1, -1);
    } else {
        fprintf(stderr, "Error: was not able to solve");
    }

    return 0;
}

int isValidBoard(char b[9][9], int x, int y) 
{
    if (!isdigit(b[y][x])) {
        return 0;
    }

    // Check horizontal nums are different
    for (int hor=0; hor<9; hor++) {
        if (hor != x && b[y][x] == b[y][hor]) {
            return 0;
        }
    }

    // Check vertical nums are different
    for (int ver=0; ver<9; ver++) {
        if (ver != y && b[y][x] == b[ver][x]) {
            return 0;
        }
    }

    // Check 3x3 nums are different
    int firstXCell = (x/3)*3;
    int firstYCell = (y/3)*3;
    for (int i=firstYCell; i<firstYCell+3; i++) {
        for (int j=firstXCell; j<firstXCell+3; j++) {
            if ((i != y && j != x) && b[i][j] == b[y][x]) {
                return 0;
            }
        }
    }

    return 1;
}

int bruteForceSolver(char b[9][9], int x, int y, int storedBacktrack) 
{
    if (x > 8 || y > 8) {
        return 1;
    }
    if (x < 0 || y < 0) {
        return 0;
    }

    if (b[y][x] != inputBoard[y][x]) {
        do {
            // Stop incrementing if num isn't a digit
            if (!isdigit(b[y][x])) {
                break;
            }
            b[y][x]++;
        }
        while (!isValidBoard(b, x, y)); 
    }

    if (!isValidBoard(b, x, y) || storedBacktrack) {
        if (b[y][x] != inputBoard[y][x]) {
            b[y][x] = '0';
        }
        x--;
        if (x < 0) {
            y--;
            x = 8;
        }

        if (b[y][x] == inputBoard[y][x]) {
            storedBacktrack = 1;
        } else {
            storedBacktrack = 0;
        }
    } else {
        x++;
        if (x > 8) {
            y++;
            x = 0;
        }
    }
    if (bruteForceSolver(b, x, y, storedBacktrack)) {
        return 1;
    }
    
    return 0;
}

#define BOLD  "\033[1m"
#define BDEND "\033[m"
#define GREEN "\033[0;32m"
#define GREND "\033[0;37m"

void printBoard(char b[9][9], int x, int y) 
{
    printf("\n");

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

