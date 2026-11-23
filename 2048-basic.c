#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4
#define WIN_SCORE 2048
#define ITEM_INTERVAL 20

int board[SIZE][SIZE];
int score = 0;
int items = 0;
int turn = 0;

void init_board(void);
void print_board(void);
int is_full(void);
int is_end(void);
int can_move(void);
int move(char dir);
int use_item(void);

int main(void) {
    srand((unsigned int)time(NULL));
    init_board();
    print_board();

    while (1) {
        if (is_end()) {
            printf("The end\n");
            break;
        }

        if (is_full() && !can_move()) {
            printf("Game over\n");
            break;
        }

        char direction;
        printf("Enter move (W/A/S/D) or use item (E): ");
        if (scanf(" %c", &direction) != 1) {
            break;
        }

        if (direction == 'e' || direction == 'E') {
            if (use_item()) {
                print_board();
            }
            else {
                print_board();
                printf("No items or 2 is not on the board.\n");
            }
            continue;
        }

        if (move(direction)) {
            turn++;
            if (turn % ITEM_INTERVAL == 0) {
                items++;
            }
            print_board();
            if (turn % ITEM_INTERVAL == 0) {
                printf("20 turns reached. Items +1 (items: %d)\n", items);
            }
        }
    }

    return 0;
}

void print_board(void) {
    system("cls");
    printf("Score: %d | Items: %d | Turn: %d\n", score, items, turn);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%4d", board[i][j]);
        }
        printf("\n");
    }
}

void init_board(void) {
    score = 0;
    items = 0;
    turn = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }

    for (int k = 0; k < 2; k++) {
        int i = rand() % SIZE;
        int j = rand() % SIZE;
        while (board[i][j] != 0) {
            i = rand() % SIZE;
            j = rand() % SIZE;
        }
        board[i][j] = (rand() % 2 + 1) * 2;
    }
}

int is_full(void) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

int is_end(void) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == WIN_SCORE) {
                return 1;
            }
        }
    }
    return 0;
}

int can_move(void) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 1;
            }
            if (j > 0 && board[i][j] == board[i][j - 1]) {
                return 1;
            }
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) {
                return 1;
            }
            if (i > 0 && board[i][j] == board[i - 1][j]) {
                return 1;
            }
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) {
                return 1;
            }
        }
    }
    return 0;
}

// 2를 4로 바꾸는 아이템
int use_item(void) {
    if (items <= 0) {
        return 0;
    }

    int changed = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 2) {
                board[i][j] = 4;
                changed = 1;
            }
        }
    }

    if (!changed) {
        return 0; // 2가 없으면 무효
    }

    items--;
    return 1;
}

int move(char dir) {
    int moved = 0;
    int prev_board[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            prev_board[i][j] = board[i][j];
        }
    }

    if (dir == 'w' || dir == 'W') {
        for (int j = 0; j < SIZE; j++) {
            for (int i = 1; i < SIZE; i++) {
                if (board[i][j] != 0) {
                    int k = i;
                    while (k > 0 && board[k - 1][j] == 0) {
                        board[k - 1][j] = board[k][j];
                        board[k][j] = 0;
                        k--;
                        moved = 1;
                    }
                    if (k > 0 && board[k - 1][j] == board[k][j]) {
                        board[k - 1][j] *= 2;
                        score += board[k - 1][j];
                        board[k][j] = 0;
                        moved = 1;
                    }
                }
            }
        }
    }
    else if (dir == 's' || dir == 'S') {
        for (int j = 0; j < SIZE; j++) {
            for (int i = SIZE - 2; i >= 0; i--) {
                if (board[i][j] != 0) {
                    int k = i;
                    while (k < SIZE - 1 && board[k + 1][j] == 0) {
                        board[k + 1][j] = board[k][j];
                        board[k][j] = 0;
                        k++;
                        moved = 1;
                    }
                    if (k < SIZE - 1 && board[k + 1][j] == board[k][j]) {
                        board[k + 1][j] *= 2;
                        score += board[k + 1][j];
                        board[k][j] = 0;
                        moved = 1;
                    }
                }
            }
        }
    }
    else if (dir == 'a' || dir == 'A') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 1; j < SIZE; j++) {
                if (board[i][j] != 0) {
                    int k = j;
                    while (k > 0 && board[i][k - 1] == 0) {
                        board[i][k - 1] = board[i][k];
                        board[i][k] = 0;
                        k--;
                        moved = 1;
                    }
                    if (k > 0 && board[i][k - 1] == board[i][k]) {
                        board[i][k - 1] *= 2;
                        score += board[i][k - 1];
                        board[i][k] = 0;
                        moved = 1;
                    }
                }
            }
        }
    }
    else if (dir == 'd' || dir == 'D') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE - 2; j >= 0; j--) {
                if (board[i][j] != 0) {
                    int k = j;
                    while (k < SIZE - 1 && board[i][k + 1] == 0) {
                        board[i][k + 1] = board[i][k];
                        board[i][k] = 0;
                        k++;
                        moved = 1;
                    }
                    if (k < SIZE - 1 && board[i][k + 1] == board[i][k]) {
                        board[i][k + 1] *= 2;
                        score += board[i][k + 1];
                        board[i][k] = 0;
                        moved = 1;
                    }
                }
            }
        }
    }

    if (moved) {
        int i = rand() % SIZE;
        int j = rand() % SIZE;
        while (board[i][j] != 0) {
            i = rand() % SIZE;
            j = rand() % SIZE;
        }
        board[i][j] = (rand() % 2 + 1) * 2;
        return 1;
    }
    else {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = prev_board[i][j];
            }
        }
        return 0;
    }
}
