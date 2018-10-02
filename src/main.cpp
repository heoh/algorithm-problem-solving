#include <cstdio>
#include <malloc.h>

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

template <typename T, typename Comparator>
class PriorityQueue {
private:
	T* elements;
	int nElements;
	Comparator compare;

private:
	void swap(T& a, T& b) {
		T tmp = a;
		a = b;
		b = tmp;
	}

	void stabilizeUp(int node) {
		int child = node;
		while (child > 1) {
			int parent = child / 2;
			if (compare(elements[child], elements[parent])) {
				break;
			}
			
			swap(elements[child], elements[parent]);
			child = parent;
		}
	}

	void stabilizeDown(int node) {
		int parent = node;
		while (parent < nElements) {
			int left = parent * 2;
			int right = left + 1;

			bool hasLeft = (left <= nElements);
			bool hasRight = (right <= nElements);
			if (!hasLeft) {
				break;
			}

			int child = left;
			if (hasRight) {
				child = (compare(elements[left], elements[right])) ? right : left;
			}

			if (compare(elements[child], elements[parent])) {
				break;
			}

			swap(elements[child], elements[parent]);
			parent = child;
		}
	}

public:
	PriorityQueue(int capacity) {
		elements = (T*)malloc(sizeof(T) * (capacity + 1));
		nElements = 0;
	}

	~PriorityQueue() {
		free(elements);
	}

	const T& top() {
		return elements[1];
	}

	void push(const T& val) {
		nElements += 1;
		elements[nElements] = val;

		stabilizeUp(nElements);
	}

	void pop() {
		elements[1] = elements[nElements];
		nElements -= 1;

		stabilizeDown(1);
	}

	bool empty() {
		return nElements == 0;
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

	PriorityQueue<State, StateComparator> states(10000);

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
