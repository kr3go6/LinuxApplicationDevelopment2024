#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 6
#define DIRS_N 4

typedef struct {
    int x;
    int y;
} Point;

Point dirs[] = {{-2, 0}, {0, 2}, {2, 0}, {0, -2}};

int CanMove(char lab[SIZE][SIZE], int x, int y) {
    return 0 < x && x < SIZE && 0 < y && y < SIZE && lab[x][y] == '#';
}

void MakePassages(char lab[SIZE][SIZE], int x, int y, int depth) {
    lab[x][y] = '.';

    int tmp = rand();
    int idxs[] = {tmp % DIRS_N, (tmp + 1) % DIRS_N, (tmp + 2) % DIRS_N, (tmp + 3) % DIRS_N};

    for (int i = 0; i < DIRS_N; i++) {
        int x_dif = dirs[idxs[i]].x;
        int y_dif = dirs[idxs[i]].y;

        if (CanMove(lab, x + x_dif, y + y_dif)) {
            lab[x + x_dif / 2][y + y_dif / 2] = '.';
            MakePassages(lab, x + x_dif, y + y_dif, depth + 1);
        }
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int size = SIZE * 2 + 1;
    char lab[size][size];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            lab[i][j] = '#';
        }
    }

    MakePassages(lab, 1, 1, 0);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c", lab[i][j]);
        }
        printf("\n");
    }

    return 0;
}
