#include <cstdio>
#include <algorithm>
#include <cstdint>
#include <list>
using namespace std;

const int MAX_N = 100000;

int visited[3];
int nVisited;

class Column {
public:
    int x[3];
    int len;

    Column() {
    }

    bool operator <(const Column &obj) const {
        return this->x[0] < obj.x[0];
    }

    void init(int id) {
        x[0] = id;
        len = 1;
    }

    void add(int val) {
        for (int i = 0; i < len; i++) {
            if (x[i] == val) {
                return;
            }
        }

        x[len] = val;
        len += 1;
    }

    bool isVisited() {
        int id = x[0];
        for (int i = 0; i < nVisited; i++) {
            if (visited[i] == id) {
                return true;
            }
        }
        return false;
    }

    int visit();

    int countCycle() {
        nVisited = 0;
        return visit();
    }
};


int N;
Column columns[MAX_N];

int Column::visit() {
    visited[nVisited] = x[0];
    nVisited++;

    for (int i = 1; i < len; i++) {
        int dst = x[i];
        Column& col = columns[dst];
        if (col.isVisited()) {
            continue;
        }

        if (nVisited >= 3) {
            return 4;
        }
        if (col.visit() > 3) {
            return 4;
        }
    }

    return nVisited;
}


int solve() {
    sort(columns, columns + N);

    list<int> nMaxes[4];

    for (int i = 0; i < N; i++) {
        int nCycle = columns[i].countCycle();
        if (nCycle > 3) {
            continue;
        }

        if (nCycle == 2) {
            for (int i = 0; i < N; i++) {
                if (!columns[i].isVisited()) {
                    return N - 3;
                }
            }
        }
        if (nCycle == 3) {
            return N - nCycle;
        }
        nMaxes[nCycle].push_back(i);
    }

    if (nMaxes[1].size() >= 3) {
        return N - 3;
    }
    if (nMaxes[2].size() >= 1) {
        return N - 2;
    }
    if (nMaxes[1].size() >= 1) {
        return N - nMaxes[1].size();
    }

    return -1;
}

int main() {
    int T;
    scanf("%d", &T);

    for (int tc = 1; tc <= T; tc++) {
        scanf("%d", &N);

        for (int i = 0; i < N; i++) {
            int id;
            scanf("%d", &id);
            columns[i].init(id - 1);
        }

        for (int j = 1; j < 3; j++) {
            for (int i = 0; i < N; i++) {
                int id;
                scanf("%d", &id);
                columns[i].add(id - 1);
            }
        }

        int answer = solve();
        printf("#%d %d\n", tc, answer);
    }

    return 0;
}
