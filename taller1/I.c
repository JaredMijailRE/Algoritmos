// https://vjudge.net/contest/713089#problem/I

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define GRID_SIZE 9
#define EMPTY_CELL '.'

void print_grid(char grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

bool is_safe(char grid[GRID_SIZE][GRID_SIZE], int row, int col, char num_char) {
    // Check row
    for (int c = 0; c < GRID_SIZE; c++) {
        if (grid[row][c] == num_char) {
            return false;
        }
    }

    // Check column
    for (int r = 0; r < GRID_SIZE; r++) {
        if (grid[r][col] == num_char) {
            return false;
        }
    }

    // Check 3x3 subgrid
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (grid[r + start_row][c + start_col] == num_char) {
                return false;
            }
        }
    }
    return true;
}

bool find_empty_location(char grid[GRID_SIZE][GRID_SIZE], int *row, int *col) {
    for (*row = 0; *row < GRID_SIZE; (*row)++) {
        for (*col = 0; *col < GRID_SIZE; (*col)++) {
            if (grid[*row][*col] == EMPTY_CELL) {
                return true;
            }
        }
    }
    return false; 
}


bool solve_sudoku(char grid[GRID_SIZE][GRID_SIZE]) {
    int row, col;

    if (!find_empty_location(grid, &row, &col)) {
        return true; 
    }

    for (int num = 1; num <= 9; num++) {
        char num_char = num + '0'; 
        if (is_safe(grid, row, col, num_char)) {
            grid[row][col] = num_char;

            if (solve_sudoku(grid)) {
                return true;
            }

            grid[row][col] = EMPTY_CELL;
        }
    }
    return false;
}

int main() {
    int t;
    scanf("%d", &t);
   
    int temp_char;
    temp_char = getchar(); 

    for (int case_num = 1; case_num <= t; case_num++) {
     
        char line_buffer[GRID_SIZE + 2]; 
        if (fgets(line_buffer, sizeof(line_buffer), stdin) == NULL && case_num > 0) {

        }


        char grid[GRID_SIZE][GRID_SIZE];
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                scanf(" %c", &grid[i][j]); 
            }
        }
      
        if (case_num < t || t == 1 ) { 
            while((temp_char = getchar()) != '\n' && temp_char != EOF);
        }


        printf("Case %d:\n", case_num);
        if (solve_sudoku(grid)) {
            print_grid(grid);
        } else {
           
            printf("No solution exists (this should not happen for this problem).\n");
        }
    }
    return 0;
}