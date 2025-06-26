#include "bits/stdc++.h"
using namespace std;
const int MAXN = 2e5 + 3; 
struct Query
{
    int x, ya, yb;
    Query(int _x, int _ya, int _yb) : x(_x), ya(_ya), yb(_yb) {}; 
}; 
struct node
{
    int B, W, L, R; 
    node(int _L, int _R, int _B, int _W) : L(_L), R(_R), B(_B), W(_W) {}; 
}; 
int lazy[MAXN * 4]; 
int tree[MAXN * 4];
vector<int> coord{-1};
int M; 
void push_down(int p, int L, int mid, int R)
{
    if (lazy[p] > 0)
    {
        lazy[2 * p]     = lazy[p] xor lazy[2 * p];
        lazy[2 * p + 1] = lazy[p] xor lazy[2 * p + 1]; 
        tree[2 * p]     = coord[mid] - coord[L - 1] - tree[2 * p]; 
        tree[2 * p + 1] = coord[R]   - coord[mid]   - tree[2 * p + 1]; 
        lazy[p] = 0;
    }
    return;
}
void update(int L, int R, int l = 1, int r = M, int p = 1)
{
    if (L > r || R < l) return;
    if (L <= l && r <= R)
    {
        tree[p] = coord[r] - coord[l - 1] - tree[p]; 
        lazy[p] = lazy[p] xor 1;
        return;  
    }
    int mid = (l + r) / 2;
    push_down(p, l, mid, r);
    update(L, R, l, mid, 2 * p);
    update(L, R, mid + 1, r, 2 * p + 1);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}
signed main(void)
{
    int N;
    while(cin >> N)
    {
        vector<Query>Q; 
        for(int i = 0; i < N; i++)
        {
            int xa, ya, xb, yb;
            cin >> xa >> ya >> xb >> yb; 
            Q.push_back({xa, ya, yb});
            Q.push_back({xb, ya, yb}); 
            coord.push_back(ya); 
            coord.push_back(yb); 
        }
        auto cmp = [&](Query a, Query b)
        {
            return a.x < b.x; 
        };
        sort(coord.begin(), coord.end());
        coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
        M = coord.size() - 1; 
        sort(Q.begin(), Q.end(), cmp);  
        int64_t ret = 0;
        for(int i = 0; i < Q.size() - 1; i++)
        {
            auto [_, l, r] = Q[i]; 
            int L = lower_bound(coord.begin(), coord.end(), l) - coord.begin(); 
            int R = lower_bound(coord.begin(), coord.end(), r) - coord.begin(); 
            update(L + 1, R); 
            ret += 1LL * (Q[i + 1].x - Q[i].x) * tree[1]; 
            //cout << tree[1] << " " << Q[i + 1].x << " " << Q[i].x << '\n'; 
        }
        cout << ret << '\n'; 
    }
    return 0; 
}