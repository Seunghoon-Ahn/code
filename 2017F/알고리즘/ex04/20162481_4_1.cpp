//#2 Sudoku
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int Sudoku[9][9];
bool RowCheck[9][10], ColCheck[9][10], SquareCheck[9][10];

void solveSudoku(void) {
    int row = -1;
    int column = -1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!Sudoku[i][j]) {
                row = i;
                column = j;
                break;
            }
        }
        if (row != -1) 
            break;
    }

    if (row == -1) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                printf("%d", Sudoku[i][j]);
            }
            printf("\n");
        }
        exit(1);
    }

    int sq = 3 * (row / 3) + (column / 3);
    for (int i = 1; i <= 9; i++) {
        bool &rUsed = RowCheck[row][i];
        bool &cUsed = ColCheck[column][i];
        bool &sUsed = SquareCheck[sq][i];
        if (!rUsed && !cUsed && !sUsed) {
            rUsed = cUsed = sUsed = true;
            Sudoku[row][column] = i;
            solveSudoku();
            Sudoku[row][column] = 0;
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
