/*
 * 풀이 방법: 문자열을 시각화하여 산처럼 생각하였다.
 * 00 -> 지상 (__)
 * 01 -> 오르막 (_/)
 * 10 -> 내리막 (\_)
 * 11 -> 고원 (--)
 */

#include <cstdio>
#include <algorithm>
using namespace std;

int A, B, C, D;

bool isPossible() {
    int nSlopes = B + C;
    if ((nSlopes == 0) && ((A > 0) && (D > 0))) return false;
    
    int dSlopes = abs(B - C);
    if (dSlopes > 1) return false;

    return true;
}

int main() {
    int T;
    scanf("%d", &T);

    for (int tc = 1; tc <= T; tc++) {
        scanf("%d %d %d %d", &A, &B, &C, &D);

        printf("#%d ", tc);
        if (!isPossible()) {
            printf("impossible\n");
            continue;
        }
        
        int nPeaks = min(B, C);
        int nSlopes = B + C;
        if (nSlopes == 0) {
            if (A > 0) {
                for (int i = 0; i <= A; i++) {
                    printf("0");
                }
            }
            else {
                for (int i = 0; i <= D; i++) {
                    printf("1");
                }
            }
        }
        else if (B > C) {
            for (int i = 0; i <= A; i++) {
                printf("0");
            }
            for (int i = 0; i < nPeaks; i++) {
                printf("10");
            }
            for (int i = 0; i <= D; i++) {
                printf("1");
            }
        }
        else if (B < C) {
            for (int i = 0; i <= D; i++) {
                printf("1");
            }
            for (int i = 0; i < nPeaks; i++) {
                printf("01");
            }
            for (int i = 0; i <= A; i++) {
                printf("0");
            }
        }
        else {
            for (int i = 0; i <= A; i++) {
                printf("0");
            }
            for (int i = 0; i < nPeaks - 1; i++) {
                printf("10");
            }
            for (int i = 0; i <= D; i++) {
                printf("1");
            }
            printf("0");
        }
        printf("\n");
    }

    return 0;
}
