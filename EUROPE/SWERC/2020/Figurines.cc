#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int) x.size()

struct node {
    int val = 0, L = -1, R = -1;
};

const int maxn = 1e5 + 10;

unordered_map<int, node> tree;
int root[maxn];
int n, idx = 0;

int
build(int l, int r) {
    int c = idx++;
    if (l == r) return c;
    int mid = (l + r) / 2;
    int lson = build(l, mid);
    int rson = build(mid + 1, r);
    tree[c] = {tree[lson].val + tree[rson].val, lson, rson};
    return c;
}

int
update(int pos, int L, int R, int v, int pre) {
    if (pos < L || pos > R) return pre;
    int c = idx++;
    if (L == R) {
        tree[c].L = tree[pre].L, tree[c].R = tree[pre].R, tree[c].val = tree[pre].val + v;
        return c;
    }
    int mid = (L + R) / 2;
    tree[c].L = update(pos, L, mid, v, tree[pre].L);
    tree[c].R = update(pos, mid + 1, R, v, tree[pre].R);
    tree[c].val = tree[tree[c].L].val + tree[tree[c].R].val;
    return c;
}

int
query(int pos, int l, int r, int c) {
    if (pos > r) return 0;
    if (pos <= l) return tree[c].val;
    int mid = (l + r) / 2;
    return query(pos, l, mid, tree[c].L) + query(pos, mid + 1, r, tree[c].R);
}

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    root[0] = build(0, n);
    string line;
    cin.ignore();
    for (int i = 1; i <= n; i++) {
        getline(cin, line);
        stringstream ss(line);
        string word;
        root[i] = root[i - 1];
        while (ss >> word) {
            int x = atoi(word.substr(1).c_str());
            int y = (word[0] == '+' ? 1 : -1);
            root[i] = update(x, 0, n, y, root[i]);
        }
    }
    int64_t ret = 0;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        int curr = query(ret, 0, n, root[x]);
        ret = (ret + curr) % n;
    }
    cout << ret << '\n';
    return 0;
}