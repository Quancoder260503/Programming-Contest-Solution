#include "bits/stdc++.h"

using namespace std;

const int maxf = 500002;
const int LOG = 19;

int par[LOG][maxf], h[maxf], n, a, b;
vector<int> g[maxf];
double ret, ctra[maxf], ctrb[maxf];

int jump(int x, int d)
{
    for (int i = 0; i < LOG; i++)
    {
        if (d & (1 << i))
            x = par[i][x];
    }
    return x;
}

void dfs(int u)
{
    for (int i = 1; i < LOG; i++)
    {
        par[i][u] = par[i - 1][par[i - 1][u]];
    }
    for (auto v : g[u])
    {
        h[v] = h[par[0][v] = u] + 1;
        dfs(v);
    }
    if (h[u] >= a)
    {
        ctra[jump(u, a)] += ctra[u];
    }
    if (h[u] >= b)
    {
        ctrb[jump(u, b)] += ctrb[u];
    }
    ret += 1.0 * (ctra[u] + ctrb[u]) / n - (ctra[u] * ctrb[u]) / (1LL * n * n);
    return;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    for (int _ = 0; _ < tc; _++)
    {
        cin >> n >> a >> b;
        for (int i = 0; i < n; i++)
        {
            par[0][i] = h[i] = 0;
            ctra[i] = ctrb[i] = 1.0;
            g[i].clear();
        }
        for (int i = 1, fa; i < n; i++)
        {
            cin >> fa;
            g[--fa].push_back(i);
        }
        ret = 0.0;
        dfs(0);
        cout << "Case #" << _ + 1 << ": ";
        cout << fixed << setprecision(10) << ret << '\n';
    }
    return 0;
}