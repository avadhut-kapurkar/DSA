int compare(const void *a, const void *b)
 {
    return (*(int *)b - *(int *)a);
}
int minimumCost(int* cost, int costSize)
 {
    qsort(cost, costSize, sizeof(int), compare);
    int total = 0;
    for (int i = 0; i < costSize; i++)
     {
        if ((i + 1) % 3 != 0) {
            total += cost[i];
        }
    }
    return total;
}