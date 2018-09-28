#include <cstdio>

int T;
int N, M;
char map[50][101];

char* findRawcode() {
	for (int i = 0; i < N; i++) {
		for (int j = M - 1; j >= 55; j--) {
			if (map[i][j] == '1') {
				return &map[i][j - 55];
			}
		}
	}

	return NULL;
}

char raw2bits(char* raws) {
	char bits = 0;
	for (int i = 0; i < 7; i++) {
		bits <<= 1;
		if (raws[i] == '1') {
			bits |= 0x1;
		}
	}
	return bits;
}

int bits2code(char bits) {
	static int cache[256];
	static bool init = false;
	if (!init) {
		init = true;
		cache[0x0d] = 0;
		cache[0x19] = 1;
		cache[0x13] = 2;
		cache[0x3d] = 3;
		cache[0x23] = 4;
		cache[0x31] = 5;
		cache[0x2f] = 6;
		cache[0x3b] = 7;
		cache[0x37] = 8;
		cache[0x0b] = 9;
	}

	return cache[bits];
}

void parseCode(int dst[8]) {
	char* rawcode = findRawcode();

	for (int i = 0; i < 8; i++) {
		char bits = raw2bits(&rawcode[i * 7]);
		int code = bits2code(bits);
		dst[i] = code;
	}
}

bool validate(int code[8]) {
	int sumOfOdds = code[0] + code[2] + code[4] + code[6];
	int sumOfEvens = code[1] + code[3] + code[5];
	int validation = code[7];
	return (((sumOfOdds * 3) + sumOfEvens + validation) % 10 == 0);
}

int sum(int arr[], int start, int end) {
	int sum = 0;
	for (int i = start; i < end; i++) {
		sum += arr[i];
	}
	return sum;
}

int solve() {
	int code[8];
	parseCode(code);

	if (validate(code)) {
		return sum(code, 0, 8);
	}
	else {
		return 0;
	}
}

int main() {
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			scanf("%s", map[i]);
		}

		int answer = solve();
		printf("#%d %d\n", tc, answer);
	}

    return 0;
}
