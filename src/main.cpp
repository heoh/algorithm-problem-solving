#include <cstdio>
#include <cstring>


int map[9][9];


bool checkRow(int i) {
    bool contains[10];
    memset(contains, false, sizeof(contains));

    for (int j = 0; j < 9; j++) {
        int value = map[i][j];
        if (contains[value]) {
            return false;
        }
        contains[value] = true;
    }
    return true;
}

bool checkCol(int j) {
    bool contains[10];
    memset(contains, false, sizeof(contains));

    for (int i = 0; i < 9; i++) {
        int value = map[i][j];
        if (contains[value]) {
            return false;
        }
        contains[value] = true;
    }
    return true;
}

bool checkSquare(int r, int c) {
    bool contains[10];
    memset(contains, false, sizeof(contains));

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int value = map[r + i][c + j];
            if (contains[value]) {
                return false;
            }
            contains[value] = true;
        }
    }
    return true;
}

bool checkValid() {
    for (int i = 0; i < 9; i++) {
        if (!checkRow(i)) {
            return false;
        }
    }
    for (int i = 0; i < 9; i++) {
        if (!checkCol(i)) {
            return false;
        }
    }
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            if (!checkSquare(i, j)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);

    for (int tc = 1; tc <= T; tc++) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                scanf("%d", &map[i][j]);
            }
        }

        if (checkValid()) {
            printf("#%d %d\n", tc, 1);
        }
        else {
            printf("#%d %d\n", tc, 0);
        }
    }

    return 0;
}
