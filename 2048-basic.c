#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

int board[SIZE][SIZE] = { 0 }; // 4x4 게임판

void print_board() {
    printf("      C 2048 GAME    \n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                printf("[ . ] "); // 빈 칸
            } else {
                printf("[%3d] ", board[i][j]); // 숫자가 있으면 출력
            }
        }
        printf("\n\n");
    }
}

// 빈 칸에 2 또는 4 생성
void spawn_tile() {
    int empty_rows[SIZE * SIZE];
    int empty_cols[SIZE * SIZE];
    int count = 0;

    // 빈 칸 찾기
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                empty_rows[count] = i;
                empty_cols[count] = j;
                count++;
            }
        }
    }

    // 빈 칸이 있다면 무작위로 생성
    if (count > 0) {
        int idx = rand() % count;
        int r = empty_rows[idx];
        int c = empty_cols[idx];
        board[r][c] = (rand() % 10 == 0) ? 4 : 2;
     }
}