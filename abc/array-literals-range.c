// gcc -c array-literals-range.c
// Accepted by both gcc and clang.
// arr == {5, 5, 5, 5, 3, 3, 3, 3, 0, 0};
int arr[10] = { [0 ... 3] = 5, [4 ... 7] = 3 };

