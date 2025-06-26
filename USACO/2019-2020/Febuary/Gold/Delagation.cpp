#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)1e6 + 10
int n;
int trs[MAXN];
vector<int> adj[MAXN];
vector<int> comp[MAXN];
void dfs(int u, int p)
{
    trs[u] = 1;
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == p)
            continue;
        dfs(v, u);
        trs[u] += trs[v];
        comp[u].push_back(trs[v]);
    }
    if (u > 1)
        comp[u].push_back(n - trs[u]);
    return;
}
bool check(int k)
{
    vector<int> dp(k + 1, 0);
    for (int i = n; i > 0; i--)
    {
        int cnt = 0;
        for (int j = 0; j < comp[i].size(); j++)
        {
            int m = comp[i][j] % k;
            if (m == 0)
                continue;
            if (dp[k - m])
            {
                dp[k - m]--;
                cnt--;
            }
            else
            {
                dp[m] += 1;
                cnt++;
            }
        }
        if (cnt)
            return 0;
    }
    return 1;
}
signed main(void)
{
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i < n; i++)
    {
        if ((n - 1) % i == 0)
            cout << check(i);
        else
            cout << 0;
    }
    return 0;
}
/*

*/
