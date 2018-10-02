#include <cstdio>
#include <queue>
#include <functional>
using namespace std;

class State {
public:
	int y;
	int x;
	int time;

	State(int y_, int x_, int time_) {
		y = y_;
		x = x_;
		time = time_;
	}

	void move(int dir) {
		static int yOffsets[] = { -1, 0, 1, 0 };
		static int xOffsets[] = { 0, 1, 0, -1 };

		y += yOffsets[dir];
		x += xOffsets[dir];
	}
};

class StateComparator {
public:
	bool operator() (const State& s0, const State& s1) {
		return s0.time > s1.time;
	}
};

int T;
int N;
int Map[100][100];


bool checkGoal(const State& s) {
	return ((s.y == (N - 1)) && (s.x == (N - 1)));
}

bool validate(const State& s) {
	if ((s.y < 0) || (s.y >= N)) return false;
	if ((s.x < 0) || (s.x >= N)) return false;
	return true;
}

int solve() {
	static bool visited[100][100];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = false;
		}
	}

	priority_queue<State, vector<State>, StateComparator > states;

	visited[0][0] = true;
	states.push(State(0, 0, 0));

	while (!states.empty()) {
		State current = states.top();
		states.pop();

		if (checkGoal(current)) {
			return current.time;
		}

		for (int d = 0; d < 4; d++) {
			State next = current;
			next.move(d);

			if (!validate(next)) {
				continue;
			}
			if (visited[next.y][next.x]) {
				continue;
			}

			next.time += Map[next.y][next.x];
			visited[next.y][next.x] = true;
			states.push(next);
		}
	}

	return -1;
}

int main() {
	scanf("%d", &T);
	
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%1d", &Map[i][j]);
			}
		}

		int answer = solve();
		printf("#%d %d\n", tc, answer);
	}

    return 0;
}
