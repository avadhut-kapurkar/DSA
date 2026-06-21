int maxIceCream(int* costs, int costsSize, int coins) {
    int maxCost = 0;

    for (int i = 0; i < costsSize; i++) {
        if (costs[i] > maxCost)
            maxCost = costs[i];
    }

    int count[maxCost + 1];
    for (int i = 0; i <= maxCost; i++)
        count[i] = 0;

    for (int i = 0; i < costsSize; i++)
        count[costs[i]]++;

    int ans = 0;

    for (int price = 1; price <= maxCost; price++) {
        while (count[price] > 0 && coins >= price) {
            coins -= price;
            ans++;
            count[price]--;
        }
    }

    return ans;
}