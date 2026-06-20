#include <stdlib.h>

typedef struct {
    int id;
    int h;
} Restriction;

int cmp(const void *a, const void *b) {
    Restriction *x = (Restriction *)a;
    Restriction *y = (Restriction *)b;
    return x->id - y->id;
}

int maxBuilding(int n, int** restrictions, int restrictionsSize, int* restrictionsColSize) {
    Restriction *arr = (Restriction *)malloc((restrictionsSize + 2) * sizeof(Restriction));
    int m = 0;

    arr[m].id = 1;
    arr[m].h = 0;
    m++;

    for (int i = 0; i < restrictionsSize; i++) {
        arr[m].id = restrictions[i][0];
        arr[m].h = restrictions[i][1];
        m++;
    }

    qsort(arr, m, sizeof(Restriction), cmp);

    if (arr[m - 1].id != n) {
        arr[m].id = n;
        arr[m].h = 1000000000;
        m++;
    }

    for (int i = 1; i < m; i++) {
        int d = arr[i].id - arr[i - 1].id;
        if (arr[i].h > arr[i - 1].h + d)
            arr[i].h = arr[i - 1].h + d;
    }

    for (int i = m - 2; i >= 0; i--) {
        int d = arr[i + 1].id - arr[i].id;
        if (arr[i].h > arr[i + 1].h + d)
            arr[i].h = arr[i + 1].h + d;
    }

    int ans = 0;

    for (int i = 0; i < m - 1; i++) {
        int d = arr[i + 1].id - arr[i].id;
        int peak = (arr[i].h + arr[i + 1].h + d) / 2;
        if (peak > ans)
            ans = peak;
    }

    free(arr);
    return ans;
}