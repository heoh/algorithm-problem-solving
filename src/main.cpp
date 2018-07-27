#include <cstdio>

int arr[50];


void swap(int& a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void quicksort(int arr[], int left, int right) {
    if (left >= right) return;
    
    int mid = (left + right) / 2;
    swap(arr[left], arr[mid]);
    int pivot = arr[left];

    int l = left + 1;
    int r = right;
    while (l < r) {
        while (arr[l] <= pivot && l < right) l++;
        while (arr[r] >= pivot && r > left) r--;

        if (l < r) {
            swap(arr[l], arr[r]);
        }
    }
    if (arr[left] > arr[r]) {
        swap(arr[left], arr[r]);
    }

    quicksort(arr, left, r - 1);
    quicksort(arr, r + 1, right);
}

void sort(int arr[], int n) {
    quicksort(arr, 0, n - 1);
}

int main() {
    int t;
    scanf("%d", &t);

    for (int tc = 1; tc <= t; tc++) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        sort(arr, n);

        printf("#%d", tc);
        for (int i = 0; i < n; i++) {
            printf(" %d", arr[i]);
        }
        printf("\n");
    }

    return 0;
}
