#include <cstdio>
#include <algorithm>
using namespace std;

#define ABS(x) ((x < 0) ? -x : x)

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

const int OPPOSITE[] = { DOWN, UP, RIGHT, LEFT };

typedef struct {
	int x;
	int y;
	int dir;
	int k;
	bool alive;
	float deathTime;
} Atom;

typedef struct {
	Atom* atomA;
	Atom* atomB;
	float time;
} Collision;

int T;
int N;
Atom Atoms[1000];

int initCollisions(Collision collisions[]) {
	int size = 0;
	for (int i = 0; i < N; i++) {
		Atom& atomA = Atoms[i];
		for (int j = i + 1; j < N; j++) {
			Atom& atomB = Atoms[j];

			bool collided = false;
			float time = 0.f;

			if (atomA.dir == atomB.dir) {
				continue;
			}
			else if (atomA.dir == OPPOSITE[atomB.dir]) {
				bool vertical = ((atomA.dir == UP) || (atomA.dir == DOWN));
				if (vertical) {
					if (atomA.x != atomB.x) {
						continue;
					}

					if (atomA.dir == UP) {
						if (atomA.y < atomB.y) {
							collided = true;
							time = (float)(atomB.y - atomA.y) * 0.5f;
						}
					}
					else {
						if (atomA.y > atomB.y) {
							collided = true;
							time = (float)(atomA.y - atomB.y) * 0.5f;
						}
					}
				}
				else {
					if (atomA.y != atomB.y) {
						continue;
					}

					if (atomA.dir == RIGHT) {
						if (atomA.x < atomB.x) {
							collided = true;
							time = (float)(atomB.x - atomA.x) * 0.5f;
						}
					}
					else {
						if (atomA.x > atomB.x) {
							collided = true;
							time = (float)(atomA.x - atomB.x) * 0.5f;
						}
					}
				}
			}
			else {
				int dx = atomB.x - atomA.x;
				int dy = atomB.y - atomA.y;

				if (ABS(dx) != ABS(dy)) {
					continue;
				}

				if ((atomA.dir == UP) || (atomA.dir == DOWN)) {
					if ((atomA.dir == UP) && (dy < 0)) {
						continue;
					}
					if ((atomA.dir == DOWN) && (dy > 0)) {
						continue;
					}
					if ((atomB.dir == LEFT) && (dx < 0)) {
						continue;
					}
					if ((atomB.dir == RIGHT) && (dx > 0)) {
						continue;
					}

					collided = true;
					time = (float)ABS(dx);
				}
				else if ((atomA.dir == LEFT) || (atomA.dir == RIGHT)) {
					if ((atomA.dir == LEFT) && (dx > 0)) {
						continue;
					}
					if ((atomA.dir == RIGHT) && (dx < 0)) {
						continue;
					}
					if ((atomB.dir == UP) && (dy > 0)) {
						continue;
					}
					if ((atomB.dir == DOWN) && (dy < 0)) {
						continue;
					}

					collided = true;
					time = (float)ABS(dx);
				}
			}

			if (collided) {
				collisions[size] = { &atomA, &atomB, time };
				size++;
			}
		}
	}

	return size;
}

void quickSort(Collision input[], int first, int last)
{
	int pivot;
	int i;
	int j;
	Collision temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (input[i].time <= input[pivot].time && i < last)
			{
				i++;
			}
			while (input[j].time > input[pivot].time)
			{
				j--;
			}
			if (i < j)
			{
				temp = input[i];
				input[i] = input[j];
				input[j] = temp;
			}
		}

		temp = input[pivot];
		input[pivot] = input[j];
		input[j] = temp;

		quickSort(input, first, j - 1);
		quickSort(input, j + 1, last);
	}
}

bool acompare(const Collision& lhs, const Collision& rhs) { return lhs.time < rhs.time; }

int solve() {
	static Collision collisions[200000];

	int nCollisions = initCollisions(collisions);
	//quickSort(collisions, 0, nCollisions - 1);
	sort(collisions, collisions + nCollisions, acompare);

	int sum = 0;

	for (int i = 0; i < nCollisions; i++) {
		Collision& collision = collisions[i];
		Atom& atomA = *collision.atomA;
		Atom& atomB = *collision.atomB;
		float t = collision.time;

		if (atomA.alive && atomB.alive) {
			atomA.deathTime = t;
			atomA.alive = false;
			sum += atomA.k;

			atomB.deathTime = t;
			atomB.alive = false;
			sum += atomB.k;
		}
		else if (atomA.alive) {
			if (atomB.deathTime == t) {
				atomA.deathTime = t;
				atomA.alive = false;
				sum += atomA.k;
			}
		}
		else if (atomB.alive) {
			if (atomA.deathTime == t) {
				atomB.deathTime = t;
				atomB.alive = false;
				sum += atomB.k;
			}
		}
	}

	return sum;
}

int main() {
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);

		for (int i = 0; i < N; i++) {
			Atom& atom = Atoms[i];
			scanf("%d %d %d %d", &atom.x, &atom.y, &atom.dir, &atom.k);
			atom.alive = true;
		}

		int answer = solve();
		printf("#%d %d\n", tc, answer);
	}

    return 0;
}
