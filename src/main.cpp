#include <cstdio>

int min(int a, int b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}


class Vertex {
public:
	int id;
	Vertex* parent;
	Vertex* left;
	Vertex* right;
	
	void init(int id_) {
		id = id_;
		parent = NULL;
		left = NULL;
		right = NULL;
	}

	bool addChild(Vertex* child) {
		if (left == NULL) {
			left = child;
			child->parent = this;
			return true;
		}
		if (right == NULL) {
			right = child;
			child->parent = this;
			return true;
		}
		return false;
	}
};


int T;
int V, E, V1, V2;
Vertex vertices[10001];

int depths[10001];

void initDepthRecursion(Vertex* root, int depth) {
	depths[root->id] = depth;

	if (root->left != NULL) {
		initDepthRecursion(root->left, depth + 1);
	}
	if (root->right != NULL) {
		initDepthRecursion(root->right, depth + 1);
	}
}
void initDepth() {
	Vertex* root = &vertices[1];
	initDepthRecursion(root, 1);
}

int getDepth(Vertex* v) {
	return depths[v->id];
}


int searchLowestCommonAncestor(int v1_, int v2_) {
	initDepth();

	Vertex* v1 = &vertices[v1_];
	Vertex* v2 = &vertices[v2_];

	int minDepth = min(getDepth(v1), getDepth(v2));
	while (getDepth(v1) > minDepth) {
		v1 = v1->parent;
	}
	while (getDepth(v2) > minDepth) {
		v2 = v2->parent;
	}

	while (v1 != v2) {
		v1 = v1->parent;
		v2 = v2->parent;
	}

	return v1->id;
}

int countTreeSize(Vertex* root) {
	int cnt = 1;

	if (root->left) {
		cnt += countTreeSize(root->left);
	}
	if (root->right) {
		cnt += countTreeSize(root->right);
	}

	return cnt;
}


int main() {
	scanf("%d", &T);
	
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d %d %d", &V, &E, &V1, &V2);

		for (int i = 1; i <= V; i++) {
			vertices[i].init(i);
		}

		for (int i = 0; i < E; i++) {
			int parent, child;
			scanf("%d %d", &parent, &child);

			vertices[parent].addChild(&vertices[child]);
		}

		int lca = searchLowestCommonAncestor(V1, V2);
		int size = countTreeSize(&vertices[lca]);
		printf("#%d %d %d\n", tc, lca, size);
	}

    return 0;
}
