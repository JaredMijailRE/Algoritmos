#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define N          9
#define EMPTY_CELL '.'

static int row_mask[N], col_mask[N], box_mask[N];

typedef struct { int r, c; } Cell;
static Cell empties[81];
static int  empty_count;

static char grid[N][N];

static inline int box_index(int r, int c) {
    return (r/3)*3 + (c/3);
}

/**
 * @param used_mask 
 * @param depth     
 */
static inline int popcount9(int x) {
    return __builtin_popcount(x);
}

 
  

static bool solve_sudoku(int depth) {
    if (depth == empty_count) {
        return true;
    }

    int best_idx   = -1;
    int best_count = 10;  

    for (uint8_t i = depth; i < empty_count; i++) {
        int r = empties[i].r;
        int c = empties[i].c;
        int b = box_index(r, c);

        int used = row_mask[r] | col_mask[c] | box_mask[b];
        int cand = (~used) & 0x1FF;  

        int cnt = popcount9(cand);
        if (cnt < best_count) {
            best_count = cnt;
            best_idx   = i;
            if (cnt == 1) {
                break;
            }
        }
    }

    if (best_idx < 0 || best_count == 0) {
        return false;
    }

    if (best_idx != depth) {
        Cell tmp        = empties[depth];
        empties[depth]  = empties[best_idx];
        empties[best_idx] = tmp;
    }

    int r = empties[depth].r;
    int c = empties[depth].c;
    int b = box_index(r, c);

    int used = row_mask[r] | col_mask[c] | box_mask[b];
    int cand = (~used) & 0x1FF;  
    while (cand) {
        int pick_bit = cand & (-cand);
        cand ^= pick_bit;  

        int d = __builtin_ctz(pick_bit) + 1;  

        grid[r][c]       = '0' + d;
        row_mask[r]     |= (1 << (d-1));
        col_mask[c]     |= (1 << (d-1));
        box_mask[b]     |= (1 << (d-1));

        if (solve_sudoku(depth + 1)) {
            return true;
        }

        grid[r][c]      = EMPTY_CELL;
        row_mask[r]    &= ~(1 << (d-1));
        col_mask[c]    &= ~(1 << (d-1));
        box_mask[b]    &= ~(1 << (d-1));
    }

    if (best_idx != depth) {
        Cell tmp         = empties[depth];
        empties[depth]   = empties[best_idx];
        empties[best_idx] = tmp;
    }
    return false;
}

static void print_grid(void) {
    for (uint8_t i = 0; i < N; i++) {
        for (uint8_t j = 0; j < N; j++) {
            putchar(grid[i][j]);
        }
        putchar('\n');
    }
}

int main(void) {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    int ch = getchar();
    (void)ch;

    for (int case_num = 1; case_num <= T; case_num++) {
        
        for (uint8_t i = 0; i < N; i++) {
            for (uint8_t j = 0; j < N; j++) {
                char x;
                
                do {
                    if (scanf("%c", &x) != 1) x = 0;
                } while (!( (x >= '1' && x <= '9') || (x == EMPTY_CELL) ));
                grid[i][j] = x;
            }
        }

        for (uint8_t i = 0; i < N; i++) {
            row_mask[i] = 0;
            col_mask[i] = 0;
            box_mask[i] = 0;
        }
        empty_count = 0;

        for (uint8_t i = 0; i < N; i++) {
            for (uint8_t j = 0; j < N; j++) {
                char c = grid[i][j];
                if (c == EMPTY_CELL) {
                    empties[empty_count].r = i;
                    empties[empty_count].c = j;
                    empty_count++;
                } else {
                    int d = c - '0';  
                    int bit = 1 << (d - 1);
                    row_mask[i]   |= bit;
                    col_mask[j]   |= bit;
                    box_mask[box_index(i,j)] |= bit;
                }
            }
        }

        bool solved = solve_sudoku(0);
        printf("Case %d:\n", case_num);
        print_grid();
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
    return 0;
}
