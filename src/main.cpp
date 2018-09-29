#include <cstdio>


int T;
int N;
int x[10];
int m[10];


double calculateForce(double p) {
	double totalForce = 0.;
	for (int i = 0; i < N; i++) {
		double d = (double)x[i] - p;
		double f = (double)m[i] / (d * d);
		
		if (d < 0) {
			totalForce -= f;
		}
		else {
			totalForce += f;
		}
	}

	return totalForce;
}

double searchBalanceX(double left, double right) {
	static const double ERROR = 1e-12;

	double mid = (left + right) / 2;
	if ((right - left) <= ERROR) {
		return mid;
	}

	double f = calculateForce(mid);
	if (f == 0.) {
		return mid;
	}
	else if (f > 0) {
		return searchBalanceX(left, mid);
	}
	else {
		return searchBalanceX(mid, right);
	}
}

int solve(double answers[]) {
	for (int i = 0; i < N - 1; i++) {
		answers[i] = searchBalanceX(x[i], x[i + 1]);
	}

	return N - 1;
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &x[i]);
		}
		for (int i = 0; i < N; i++) {
			scanf("%d", &m[i]);
		}
		
		double answers[10];
		int nAnswers = solve(answers);

		printf("#%d", tc);
		for (int i = 0; i < nAnswers; i++) {
			printf(" %.10lf", answers[i]);
		}
		printf("\n");
	}

    return 0;
}
