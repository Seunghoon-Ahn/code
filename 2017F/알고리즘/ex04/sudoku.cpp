//#2 Sudoku
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int Sudoku[9][9];
bool RowCheck[9][10], ColCheck[9][10], SquareCheck[9][10];

void solveSudoku(void) {
    int r = -1, c = -1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!Sudoku[i][j]) {
                r = i;
                c = j;
                break;
            }
        }

        if (r != -1) 
            break;
    }

    if (r == -1) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                printf("%d", Sudoku[i][j]);
            }
            printf("\n");
        }
        exit(1);
    }

    int s = 3 * (r / 3) + (c / 3);
    for (int i = 1; i <= 9; i++) {
        bool &rUsed = RowCheck[r][i];
        bool &cUsed = ColCheck[c][i];
        bool &sUsed = SquareCheck[s][i];
        if (!rUsed && !cUsed && !sUsed) {
            rUsed = cUsed = sUsed = true;
            Sudoku[r][c] = i;
            solveSudoku();
            Sudoku[r][c] = 0;
            rUsed = cUsed = sUsed = false;
        }
    }
}

int main(void) {
 
    for (int i = 0; i<9; i++) {
        for (int j = 0; j<9; j++) {
            int &tmp = Sudoku[i][j];
            tmp = getchar() - '0';

            RowCheck[i][tmp] = true;
            ColCheck[j][tmp] = true;
            SquareCheck[3 * (i / 3) + (j / 3)][tmp] = true;
        }
        getchar();
    }
    solveSudoku();
    return 0;
}
