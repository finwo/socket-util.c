#include <stdlib.h>
#include "socket-util.h"
#include "test.h"

void test_merge_fd_arrays_single() {
    int *arr1 = malloc(sizeof(int) * 3);
    arr1[0] = 2;
    arr1[1] = 5;
    arr1[2] = 10;

    int *arrays[] = { arr1 };
    int *result = merge_fd_arrays(arrays, 1);

    ASSERT("single array merge - count", result[0] == 2);
    ASSERT("single array merge - first", result[1] == 5);
    ASSERT("single array merge - second", result[2] == 10);

    free(result);
}

void test_merge_fd_arrays_multiple() {
    int *arr1 = malloc(sizeof(int) * 3);
    arr1[0] = 2;
    arr1[1] = 1;
    arr1[2] = 2;

    int *arr2 = malloc(sizeof(int) * 3);
    arr2[0] = 2;
    arr2[1] = 3;
    arr2[2] = 4;

    int *arrays[] = { arr1, arr2 };
    int *result = merge_fd_arrays(arrays, 2);

    ASSERT("multiple array merge - count", result[0] == 4);
    ASSERT("multiple array merge - first", result[1] == 1);
    ASSERT("multiple array merge - second", result[2] == 2);
    ASSERT("multiple array merge - third", result[3] == 3);
    ASSERT("multiple array merge - fourth", result[4] == 4);

    free(result);
}

void test_merge_fd_arrays_empty() {
    int *arr1 = malloc(sizeof(int) * 1);
    arr1[0] = 0;

    int *arrays[] = { arr1 };
    int *result = merge_fd_arrays(arrays, 1);

    ASSERT("empty array merge", result == NULL);
}

void test_merge_fd_arrays_null() {
    int *result = merge_fd_arrays(NULL, 0);
    ASSERT("null arrays", result == NULL);
}

int main() {
    RUN(test_merge_fd_arrays_single);
    RUN(test_merge_fd_arrays_multiple);
    RUN(test_merge_fd_arrays_empty);
    RUN(test_merge_fd_arrays_null);
    return TEST_REPORT();
}
