#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e5 + 10;
#define lint long long
int fa[MAXN];
lint ccost[MAXN];
int n;
vector<pair<lint, pair<int, int>>> Edge;
vector<pair<lint, pair<int, int>>> Edge2;
vector<pair<lint, pair<int, int>>> Edge3;
int find(int u)
{
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}
signed main(void)
{
    cin >> n;
    iota(fa + 1, fa + n + 1, 1);
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            int c;
            cin >> c;
            if (c < 0)
            {
                Edge.push_back({-c, {i, j}});
            }
            else if (c > 0)
            {
                Edge2.push_back({c, {i, j}});
            }
        }
    }
    sort(Edge.begin(), Edge.end());
    sort(Edge2.begin(), Edge2.end());
    for (int i = 0; i < Edge.size(); i++)
    {
        lint cost = Edge[i].first;
        int u = Edge[i].second.first;
        int v = Edge[i].second.second;
        if (find(u) == find(v))  continue;
        u = find(u), v = find(v);
        ccost[v] += cost + ccost[u];
        fa[u] = v;
    }
    for (int i = 0; i < Edge2.size(); i++)
    {
        lint cost = Edge2[i].first;
        int u = Edge2[i].second.first;
        int v = Edge2[i].second.second;
        u = find(u), v = find(v);
        if (u == v) continue;
        Edge3.push_back({cost + ccost[u] + ccost[v], {u, v}});
    }
    sort(Edge3.begin(), Edge3.end());
    lint ans = 0;
    for (int i = 0; i < Edge3.size(); i++)
    {
        lint cost = Edge3[i].first;
        int u = Edge3[i].second.first;
        int v = Edge3[i].second.second;
        u = find(u), v = find(v);
        if (u == v) continue;
        ans += cost;
        fa[u] = v;
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        cnt += (find(i) == i);
    }
    if (cnt > 1)
    {
        puts("impossible");
    }
    else
    {
        cout << ans << '\n';
    }
    return 0;
}