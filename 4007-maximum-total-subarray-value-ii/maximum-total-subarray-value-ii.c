typedef long long ll;

typedef struct {
    ll val;
    int l;
    int r;
} Node;

typedef struct {
    Node *a;
    int size;
} Heap;

static int lg2_[50005];
static int stMax[17][50005];
static int stMin[17][50005];

void heapSwap(Node *x, Node *y) {
    Node t = *x;
    *x = *y;
    *y = t;
}

void push(Heap *h, Node x) {
    int i = ++h->size;
    h->a[i] = x;

    while (i > 1) {
        int p = i >> 1;
        if (h->a[p].val >= h->a[i].val)
            break;

        heapSwap(&h->a[p], &h->a[i]);
        i = p;
    }
}

Node popHeap(Heap *h) {
    Node ret = h->a[1];
    h->a[1] = h->a[h->size--];

    int i = 1;

    while (1) {
        int largest = i;
        int l = i << 1;
        int r = l + 1;

        if (l <= h->size &&
            h->a[l].val > h->a[largest].val)
            largest = l;

        if (r <= h->size &&
            h->a[r].val > h->a[largest].val)
            largest = r;

        if (largest == i)
            break;

        heapSwap(&h->a[i], &h->a[largest]);
        i = largest;
    }

    return ret;
}

static inline int rangeMax(int l, int r) {
    int len = r - l + 1;
    int k = lg2_[len];

    int a = stMax[k][l];
    int b = stMax[k][r - (1 << k) + 1];

    return a > b ? a : b;
}

static inline int rangeMin(int l, int r) {
    int len = r - l + 1;
    int k = lg2_[len];

    int a = stMin[k][l];
    int b = stMin[k][r - (1 << k) + 1];

    return a < b ? a : b;
}

static inline ll valueSub(int l, int r) {
    return (ll)rangeMax(l, r) - (ll)rangeMin(l, r);
}

long long maxTotalValue(int* nums, int numsSize, int k) {
    int n = numsSize;

    lg2_[1] = 0;
    for (int i = 2; i <= n; i++)
        lg2_[i] = lg2_[i / 2] + 1;

    for (int i = 0; i < n; i++) {
        stMax[0][i] = nums[i];
        stMin[0][i] = nums[i];
    }

    int LOG = lg2_[n] + 1;

    for (int j = 1; j < LOG; j++) {
        int len = 1 << j;

        for (int i = 0; i + len <= n; i++) {
            int a = stMax[j - 1][i];
            int b = stMax[j - 1][i + (len >> 1)];
            stMax[j][i] = a > b ? a : b;

            a = stMin[j - 1][i];
            b = stMin[j - 1][i + (len >> 1)];
            stMin[j][i] = a < b ? a : b;
        }
    }

    Heap heap;
    heap.a = (Node *)malloc(sizeof(Node) * (n + k + 5));
    heap.size = 0;

    for (int l = 0; l < n; l++) {
        Node cur;
        cur.l = l;
        cur.r = n - 1;
        cur.val = valueSub(l, n - 1);
        push(&heap, cur);
    }

    ll ans = 0;

    while (k--) {
        Node cur = popHeap(&heap);

        ans += cur.val;

        if (cur.r > cur.l) {
            cur.r--;
            cur.val = valueSub(cur.l, cur.r);
            push(&heap, cur);
        }
    }

    free(heap.a);
    return ans;
}