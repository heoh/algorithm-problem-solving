#include <cstdio>

const int NUM_OF_MONEYS = 8;
const int MONEY[] = { 50000, 10000, 5000, 1000, 500, 100, 50, 10 };

void solve(int counts[NUM_OF_MONEYS], int n) {
    for (int i = 0; i < NUM_OF_MONEYS; i++) {
        counts[i] = n / MONEY[i];
        n %= MONEY[i];
    }
}

void printArray(int counts[NUM_OF_MONEYS]) {
    for (int i = 0; i < NUM_OF_MONEYS; i++) {
        printf("%d ", counts[i]);
    }
}

int main() {
    int T;
    scanf("%d", &T);

    for (int tc = 1; tc <= T; tc++) {
        int n;
        scanf("%d", &n);

        int counts[NUM_OF_MONEYS];
        solve(counts, n);

        printf("#%d\n", tc);
        printArray(counts);
        printf("\n");
    }

    return 0;
}
