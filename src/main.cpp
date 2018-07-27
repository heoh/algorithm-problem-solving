#include <cstdio>

int mat[4][7][7];
int n;


void rotate90(int src[7][7], int dst[7][7]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dst[i][j] = src[n-1-j][i];
        }
    }
}

void fillAll() {
    for (int m = 1; m < 4; m++) {
        rotate90(mat[m-1], mat[m]);
    }
}

void printAll() {
    for (int i = 0; i < n; i++) {
        for (int m = 1; m < 4; m++) {
            for (int j = 0; j < n; j++) {
                printf("%d", mat[m][i][j]);
            }
            if (m < 3) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void solve() {
    fillAll();
    printAll();
}

int main() {
    int t;
    scanf("%d", &t);

    for (int tc = 1; tc <= t; tc++) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &mat[0][i][j]);
            }
        }

        printf("#%d\n", tc);
        solve();
    }

    return 0;
}
