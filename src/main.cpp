#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdint>
#include <vector>
#include <algorithm>
using namespace std;

class Island {
public:
	int x;
	int y;
};

class Tunnel {
public:
	int head;
	int tail;
	double cost;
	
	Tunnel(int head_, int tail_, double cost_) {
		head = head_;
		tail = tail_;
		cost = cost_;
	}
};

class DisjointSet {
public:
	int* roots;

	DisjointSet(int n) {
		roots = new int[n];
		for (int i = 0; i < n; i++) {
			roots[i] = -1;
		}
	}

	~DisjointSet() {
		delete roots;
	}

	bool isRoot(int v) {
		return roots[v] < 0;
	}

	int root(int v) {
		if (isRoot(v)) {
			return v;
		}
		else {
			return roots[v] = root(roots[v]);
		}
	}

	bool isNeighbor(int a, int b) {
		int rootA = root(a);
		int rootB = root(b);

		return rootA == rootB;
	}

	void merge(int a, int b) {
		if (isNeighbor(a, b)) {
			return;
		}

		int rootA = root(a);
		int rootB = root(b);

		roots[rootA] = roots[rootA] + roots[rootB];
		roots[rootB] = rootA;
	}
};

const int MAX_NUM_OF_ISLANDS = 1000;

int T;
int N;
Island islands[MAX_NUM_OF_ISLANDS];
double E;
double costs[MAX_NUM_OF_ISLANDS][MAX_NUM_OF_ISLANDS];


double calculateCost(const Island& a, const Island& b) {
	int64_t dx = b.x - a.x;
	int64_t dy = b.y - a.y;
	int64_t dist2 = (dx * dx) + (dy * dy);
	return E * dist2;
}

void initCosts() {
	for (int i = 0; i < N; i++) {
		Island& islandA = islands[i];
		for (int j = i + 1; j < N; j++) {
			Island& islandB = islands[j];
			costs[i][j] = calculateCost(islandA, islandB);
		}
	}
}

vector<Tunnel> initTunnels() {
	vector<Tunnel> tunnels;

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			Tunnel t(i, j, costs[i][j]);
			tunnels.push_back(t);
		}
	}

	return tunnels;
}

double sumTunnelCosts(const vector<Tunnel>& tunnels) {
	double sum = 0.;
	for (int i = 0; i < tunnels.size(); i++) {
		sum += tunnels[i].cost;
	}
	return sum;
}

bool cmpTunnelByCost(const Tunnel& a, const Tunnel& b) {
	return a.cost < b.cost;
}

double findMinimumCostSpaningTree() {
	vector<Tunnel> addedTunnels;
	
	vector<Tunnel> tunnels = initTunnels();
	sort(tunnels.begin(), tunnels.end(), cmpTunnelByCost);

	DisjointSet disjSet(N);

	for (int i = 0; i < tunnels.size(); i++) {
		if (addedTunnels.size() == (N - 1)) break;

		Tunnel& t = tunnels[i];
		if (!disjSet.isNeighbor(t.head, t.tail)) {
			addedTunnels.push_back(t);
			disjSet.merge(t.head, t.tail);
		}
	}

	return sumTunnelCosts(addedTunnels);
}

double solve() {
	initCosts();
	double minCost = findMinimumCostSpaningTree();
	return minCost;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &islands[i].x);
		}
		for (int i = 0; i < N; i++) {
			scanf("%d", &islands[i].y);
		}
		scanf("%lf", &E);

		double answer = solve();
		printf("#%d %.0lf\n", tc, answer);
	}

	return 0;
}
