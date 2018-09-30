#include <cstdio>
#include <cstring>

int T;
int number, maxCnt;
int POW10[] = { 1, 10, 100, 1000, 10000, 100000, 1000000 };
int memo[1000000][11];

int countNumberLength(int n) {
	int cnt = 1;
	while (n >= 10) {
		n /= 10;
		cnt += 1;
	}
	return cnt;
}

int get(int n, int i) {
	return (n / POW10[i]) % 10;
}

int set(int n, int i, int v) {
	int left = (n / POW10[i + 1]) * POW10[i + 1];
	int right = n % POW10[i];
	return left + (v * POW10[i]) + right;
}

int swap(int number, int i, int j) {
	int a = get(number, i);
	int b = get(number, j);
	int swappedNumber = number;
	swappedNumber = set(swappedNumber, j, a);
	swappedNumber = set(swappedNumber, i, b);
	return swappedNumber;
}

int findMaxPrize(int number, int length, int cnt) {
	if (cnt == 0) {
		return number;
	}
	if (memo[number][cnt] > 0) {
		return memo[number][cnt];
	}

	int max = 0;
	for (int i = 0; i < length; i++) {
		for (int j = i + 1; j < length; j++) {
			int swappedNumber = swap(number, i, j);
			int prize = findMaxPrize(swappedNumber, length, cnt - 1);
			if (prize > max) {
				max = prize;
			}
		}
	}

	memo[number][cnt] = max;
	return max;
}

int solve() {
	int length = countNumberLength(number);
	return findMaxPrize(number, length, maxCnt);
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		memset(memo, 0, sizeof(memo));

		scanf("%d %d", &number, &maxCnt);

		int maxPrize = solve();
		printf("#%d %d\n", tc, maxPrize);
	}

    return 0;
}
