#include <cstdio>

int T;
int N, M, M2;
char hexmap[2000][501];
char map[2000][4000];

char hex2bits(char hex) {
	static bool init = false;
	static char cache[128];
	if (!init) {
		init = true;
		cache['0'] = 0;
		cache['1'] = 1;
		cache['2'] = 2;
		cache['3'] = 3;
		cache['4'] = 4;
		cache['5'] = 5;
		cache['6'] = 6;
		cache['7'] = 7;
		cache['8'] = 8;
		cache['9'] = 9;
		cache['A'] = 10;
		cache['B'] = 11;
		cache['C'] = 12;
		cache['D'] = 13;
		cache['E'] = 14;
		cache['F'] = 15;
	}

	return cache[hex];
}

void copyBits(int r, int c, char bits) {
	for (int i = 0; i < 4; i++) {
		char bin;
		if (bits & 0x8) {
			bin = '1';
		}
		else {
			bin = '0';
		}

		map[r][c + i] = bin;
		bits <<= 1;
	}
}

void initMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			char hex = hexmap[i][j];
			char bits = hex2bits(hex);
			copyBits(i, j * 4, bits);
		}
	}
	M2 = M * 4;
}

bool findTail(int& r, int& c) {
	for (int i = 0; i < N; i++) {
		for (int j = M2 - 1; j >= 55; j--) {
			if (map[i][j] == '1') {
				r = i;
				c = j;
				return true;
			}
		}
	}

	return false;
}

bool findRawcode(int& r, int& c, int& len) {
	if (!findTail(r, c)) {
		return false;
	}

	int wordLen = 0;
	while (map[r][c - wordLen] == '1') wordLen++;
	while (map[r][c - wordLen] == '0') wordLen++;
	while (map[r][c - wordLen] == '1') wordLen++;
	while (map[r][c - wordLen] == '0') wordLen++;

	len = wordLen * 8;
	c = c - len + 1;

	return true;
}

char raw2char(char* raws) {
	char bits = 0;
	for (int i = 0; i < 7; i++) {
		bits <<= 1;
		if (raws[i] == '1') {
			bits |= 0x1;
		}
	}
	return bits;
}

int char2code(char c) {
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

	return cache[c];
}

bool parseCode(int dst[8]) {
	int r, c, len;
	if (!findRawcode(r, c, len)) {
		return false;
	}

	int ratio = len / 56;
	char rawcode[56];
	for (int i = 0; i < 56; i++) {
		rawcode[i] = map[r][c + (i * ratio)];
	}

	for (int i = 0; i < 8; i++) {
		char c = raw2char(&rawcode[i * 7]);
		int code = char2code(c);
		dst[i] = code;
	}

	int rEnd;
	for (rEnd = r + 1; rEnd < N; rEnd++) {
		bool matched = true;
		for (int j = c; j < c + len; j++) {
			if (map[r][j] != map[rEnd][j]) {
				matched = false;
				break;
			}
		}
		if (!matched) {
			break;
		}
	}

	for (int i = r; i < rEnd; i++) {
		for (int j = c; j < c + len; j++) {
			map[i][j] = '0';
		}
	}

	return true;
}

bool validate(int code[8]) {
	int sumOfOdds = code[0] + code[2] + code[4] + code[6];
	int sumOfEvens = code[1] + code[3] + code[5];
	int validation = code[7];
	return (((sumOfOdds * 3) + sumOfEvens + validation) % 10 == 0);
}

int arraySum(int arr[], int start, int end) {
	int sum = 0;
	for (int i = start; i < end; i++) {
		sum += arr[i];
	}
	return sum;
}

int evalScore(int code[8]) {
	if (validate(code)) {
		return arraySum(code, 0, 8);
	}
	else {
		return 0;
	}
}

int solve() {
	initMap();

	int sum = 0;

	int code[8];
	while (parseCode(code)) {
		sum += evalScore(code);
	}

	return sum;
}

int main() {
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			scanf("%s", hexmap[i]);
		}

		int answer = solve();
		printf("#%d %d\n", tc, answer);
	}

    return 0;
}
