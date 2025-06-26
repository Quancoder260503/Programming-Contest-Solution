#include "bits/stdc++.h"
using namespace std;
#define N 1000005
#define MAXH 90
#define mp make_pair
int n, q, m;
vector<int> curr;
vector<pair<int, int> > idx[N]; 
multiset<pair<int, int> > tree[N];
struct node
{
    int x, y, h;
} A[N];
void merge(int p)
{
    for (auto it : tree[2 * p])
    {
        tree[p].insert(it);
    }
    for (auto it : tree[2 * p + 1])
    {
        tree[p].insert(it);
    }
    return;
}
void build(int l = 0, int r = m, int p = 1)
{
    if (l == r)
    {
        for(int i = 0; i < idx[l].size(); i++)
        {
            tree[p].insert(idx[l][i]); 
        } 
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * p);
    build(mid + 1, r, 2 * p + 1); 
    merge(p);
    return;
}
void query(vector<int> &curr, int lb, int rb, int L, int R, int l = 0, int r = m, int p = 1)
{
    if (L > r || R < l)
        return;
    if (L <= l && r <= R)
    {
        auto pos = tree[p].lower_bound(mp(lb, -1));
        while (curr.size() < MAXH && pos != tree[p].end() && pos->first <= rb)
        {
            curr.push_back(pos->second);
            pos++;
        }
        return;
    }
    int mid = (l + r) / 2;
    query(curr, lb, rb, L, R, l, mid, 2 * p);
    query(curr, lb, rb, L, R, mid + 1, r, 2 * p + 1);
    return;
}
signed main(void)
{
    scanf("%d%d", &n, &q);
    vector<int> vx;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &A[i].x, &A[i].y, &A[i].h);
        vx.push_back(A[i].x);
    }
    sort(vx.begin(), vx.end());
    vx.erase(unique(vx.begin(), vx.end()), vx.end());
    m = vx.size() - 1;
    for (int i = 1; i <= n; i++)
    {
        int pos = lower_bound(vx.begin(), vx.end(), A[i].x) - vx.begin();
        idx[pos].push_back(mp(A[i].y,A[i].h));  
    }
    build(); 
    int sx, sy, ex, ey;
    for (int i = 1; i <= q; i++)
    {
        scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
        sx = lower_bound(vx.begin(), vx.end(), sx) - vx.begin();
        ex = upper_bound(vx.begin(), vx.end(), ex) - vx.begin() - 1;
        curr.resize(0);
        query(curr, sy, ey, sx, ex);
        bool ans = 0;
        sort(curr.begin(), curr.end());
        for (int j = 2; j < curr.size(); j++)
        {
            if (curr[j - 2] + curr[j - 1] > curr[j])
            {
                ans = 1;
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}