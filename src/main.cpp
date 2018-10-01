#include <cstdio>

#define INT_MAX 0x7fffffff

int abs(int i) {
	if (i >= 0) {
		return i;
	}
	else {
		return -i;
	}
}

class Point {
public:
	int x;
	int y;
};

int T;
int N;
Point company;
Point home;
Point customers[10];

int getDistance(const Point& p0, const Point& p1) {
	int dx = p1.x - p0.x;
	int dy = p1.y - p0.y;
	return abs(dx) + abs(dy);
}


int findMinimumDistance(const Point& currentPos, int visited) {
	if (visited == ((1 << N) - 1)) {
		return getDistance(currentPos, home);
	}

	int min = INT_MAX;
	for (int i = 0; i < N; i++) {
		int flag = 1 << i;
		if (visited & flag) {
			continue;
		}

		int dist = getDistance(currentPos, customers[i]) + findMinimumDistance(customers[i], visited | flag);
		if (dist < min) {
			min = dist;
		}
	}

	return min;
}

int solve() {
	return findMinimumDistance(company, 0);
}

int main() {
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);

		scanf("%d %d", &company.x, &company.y);
		scanf("%d %d", &home.x, &home.y);
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &customers[i].x, &customers[i].y);
		}

		int answer = solve();
		printf("#%d %d\n", tc, answer);
	}

    return 0;
}
