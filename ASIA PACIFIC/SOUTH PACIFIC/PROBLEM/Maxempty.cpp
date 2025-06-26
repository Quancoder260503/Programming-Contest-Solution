#include "bits/stdc++.h"
using namespace std;
const int MAXN = 600;
int n, m, h;
int g[MAXN][MAXN];
int res[MAXN * MAXN];
int fa[MAXN * MAXN];
bool vis[MAXN][MAXN];
int comp[MAXN * MAXN];
int hsh(int i, int j)
{
    return m * (i - 1) + j;
}
int find(int u)
{
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}
signed main(void)
{
    cin >> n >> m >> h;
    int cnt = 0;
    vector<int>val;
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            cin >> g[i][j];
            val.push_back(g[i][j]); 
        }
    }
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            if (i > 1)
            {
                edges.push_back({max(g[i][j], g[i - 1][j]), {hsh(i, j), hsh(i - 1, j)}});
            }
            if (j > 1)
            {
                edges.push_back({max(g[i][j], g[i][j - 1]), {hsh(i, j), hsh(i, j - 1)}});
            }
        }
    }
    sort(edges.begin(), edges.end());
    iota(fa + 1, fa + n * m + 1, 1);
    fill(comp + 1, comp + n * m + 1, 1);
    memset(res, 0, sizeof(res)); 
    reverse(edges.begin(), edges.end()); 
    for (int cost = 0; cost < h - 1; cost++)
    {
        while (edges.size() && edges.back().first <= cost)
        {
            int u = edges.back().second.first;
            int v = edges.back().second.second;
            if (find(u) != find(v))
            {
                u = find(u), v = find(v);
                if (comp[u] > comp[v]) swap(u, v);
                comp[v] += comp[u];
                fa[u] = v;
            }
            edges.pop_back(); 
        }
        for (int i = 1; i < m - 1; i++)
        {
            if (g[1][i] <= cost)
            {
                res[hsh(1, i)] += comp[find(hsh(1, i))];
            }
            if (n - 2 > 1 && g[n - 2][i] <= cost)
            {
                res[hsh(n - 2, i)] += comp[find(hsh(n - 2, i))];
            }
        }
        for (int i = 2; i < n - 2; i++)
        {
            if (g[i][1] <= cost)
            {
                res[hsh(i, 1)] += comp[find(hsh(i, 1))];
            }
            if(m - 2 > 1 && g[i][m - 2] <= cost)
            {
                res[hsh(i, m - 2)] += comp[find(hsh(i, m - 2))];
            }
        }
    }
    int ans = 0;
    for (int i = 1; i < m; i++)
    {
        ans = max(ans, res[hsh(1, i)]);
        ans = max(ans, res[hsh(n - 2, i)]);
    }
    for (int i = 1; i < n; i++)
    {
        ans = max(ans, res[hsh(i, 1)]);
        ans = max(ans, res[hsh(i, m - 2)]);
    }
    cout << ans << '\n'; 
    return 0;
}
