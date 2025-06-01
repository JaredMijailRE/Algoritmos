// https://vjudge.net/contest/713089#problem/J
#include <stdio.h>
#include <stdbool.h>

char board[8][8];
int solution_count = 0;

bool is_safe(int row, int col, int queen_positions[8]) {

    for (int c = 0; c < col; c++) {
        if (queen_positions[c] == row) {
            return false;
        }
    }


    for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; r--, c--) {
        if (queen_positions[c] == r) {
            return false;
        }
    }


    for (int r = row + 1, c = col - 1; r < 8 && c >= 0; r++, c--) {
        if (queen_positions[c] == r) {
            return false;
        }
    }

    return true;
}


void solve_n_queens(int col, int queen_positions[8]) {
    
    if (col == 8) {
        solution_count++;
        return;
    }

    
    for (int i = 0; i < 8; i++) {

        if (board[i][col] == '.') {
            if (is_safe(i, col, queen_positions)) {
                queen_positions[col] = i;

                solve_n_queens(col + 1, queen_positions);
            }
        }
    }
}

int main() {
    // Read the board configuration
    for (int i = 0; i < 8; i++) {
        scanf("%s", board[i]);
    }

    int queen_positions[8]; 
                            

    solve_n_queens(0, queen_positions);

    printf("%d\n", solution_count);

    return 0;
}