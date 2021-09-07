#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <cassert>

#define OPTIMIZATION 1

struct Sub {
    int low;
    int high;
    int sum;
};

Sub FindMaximumSubarray1(const int array[], int low, int high) {
    Sub maxSub = { 0, 0, -INT_MIN};
    int count = high - low + 1;
    if (count == 1) {
        maxSub = { low, low, array[low] };
        return maxSub;
    }

    int sum[count][count];

    for (int i = 0; i < count; ++i) {
        for (int j = i; j < count; ++j) {
            if (i != j) {
                sum[i][j] = sum[i][j-1] + array[j+low];
            } else {
                sum[i][j] = array[j+low];
            }
            if (sum[i][j] > maxSub.sum) {
                maxSub = { i+low, j+low, sum[i][j] };
            }
        }
    }
    return  maxSub;
}

Sub FindMaxCross(const int array[], int low, int center, int high) {
    Sub sub = { center, center, array[center] };
    int pos = center;
    int mx = INT_MIN;
    int sum = 0;

    while (pos >= low) {
        sum += array[pos];
        if (sum > mx) {
            mx = sum;
            sub.low = pos;
        }
        --pos;
    }

    pos = center + 1;
    sum = mx;
    while (pos <= high) {
        sum += array[pos];
        if (sum > mx) {
            mx = sum;
            sub.high = pos;
        }
        ++pos;
    }
    sub.sum = mx;

    return sub;
}

Sub FindMaximumSubarray2(const int array[], int low, int high) {
    if (high == low) {
        Sub s0 = { low, high, array[low] };
        return s0;
    }
#if OPTIMIZATION
    // optimization
    if (low - high + 1 <= 20) {
        return FindMaximumSubarray1(array, low, high);
    }
#endif

    int center = (low + high) / 2;
    Sub s1 = FindMaximumSubarray2(array, low, center);
    Sub s2 = FindMaximumSubarray2(array, center + 1, high);
    Sub s3 = FindMaxCross(array, low, center, high);
    if (s1.sum >= s2.sum && s1.sum >= s3.sum) {
        return s1;
    } else if (s2.sum > s1.sum && s2.sum >= s3.sum) {
        return s2;
    }
    return s3;
}

int* GeneratetData(int count) {
    int* data = (int*)malloc(count * sizeof(int));
    for (int i = 0; i < count; ++i) {
        data[i] = rand() % 1000 - 499;
    }
    return data;
}

void DestroyData(int* data) {
    free(data);
}

int main() {
    for (int count = 4; count < 1100; ++count) {
        int* arr = GeneratetData(count);
        clock_t c1 = clock();
        Sub ans1;
        for (int i = 0; i < 200000; ++i) {
            ans1 = FindMaximumSubarray1(arr, 0, count-1);
        }
        clock_t c2 = clock();
        Sub ans2;
        for (int i = 0; i < 200000; ++i) {
            ans2 = FindMaximumSubarray2(arr, 0, count-1);
        }
        clock_t c3 = clock();
        DestroyData(arr);
        long t1 = c2 - c1;
        long t2 = c3 - c2;
        printf("count = %d t1 = %ld t2 = %ld\n", count, t1, t2);

        if (ans1.low != ans2.low || ans1.high != ans2.high || ans1.sum != ans2.sum) {
            printf("error!\n");
            exit(-1);
        }
        if (t2 < t1) {
            break;
        }
    }
    return 0;
}
