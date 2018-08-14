#include <cstdio>
#include <cmath>

long long count(int n, int b) {
    long long cnt = 0;

    int i = 2;

    int log = 2;
    long long pow = (long long) b * b;
    while (pow <= n) {
        pow *= b;
        log++;
    }


    long long unit = (1 - pow) / (1 - b);

    if (log < 2) {
        return 0;
    }

    cnt += (long long)(b - 1) * (log - 2);
    long long val = unit;
    for (int j = 1; j < b; j++) {
        if (val <= n) {
            cnt++;
            val += unit;
        }
        else {
            break;
        }
    }

    return cnt;
}

long long solve(int n) {
    long long sum = 0;

    for (int b = 2; b < n; b++) {
        sum += (long long)b * count(n, b);
    }

    return sum;
}

int main() {
    //setbuf(stdout, NULL);

    int T;
    scanf("%d", &T);

    for (int tc = 1; tc <= T; tc++) {
        int N;
        scanf("%d", &N);

        long long answer = solve(N);
        printf("#%d %lld\n", tc, answer);
    }

    return 0;
}
