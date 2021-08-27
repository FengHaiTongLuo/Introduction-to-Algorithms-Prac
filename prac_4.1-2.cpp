#include <cstdio>
#include <cstring>
#include <climits>

struct Sub {
    int low;
    int high;
    int sum;
};

Sub FindMaximumSubarray(const int array[], int count) {
    int sum[count][count];
    Sub maxSub = { 0, 0, -INT_MIN};
    for (int i = 0; i < count; ++i) {
        for (int j = i; j < count; ++j) {
            if (i != j) {
                sum[i][j] = sum[i][j-1] + array[j];
            } else {
                sum[i][j] = array[j];
            }
            if (sum[i][j] > maxSub.sum) {
                maxSub = { i, j, sum[i][j] };
            }
        }
    }
    return  maxSub;
}

int main() {
    int arr[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
    Sub ans = FindMaximumSubarray(arr, sizeof(arr)/sizeof(arr[0]));
    printf("low = %d, high = %d, sum = %d", ans.low, ans.high, ans.sum);
    return 0;
}
