#include "bits/stdc++.h"
using namespace std;
const int MAXN = 1000;
int dp[MAXN][MAXN][2];
vector<int> adj[MAXN];
int a[MAXN];
int b[MAXN];
int n, K;
void dfs(int u, int p)
{
    dp[u][a[u]][1] = b[u];
    for (auto v : adj[u])
    {
        if (v == p)
            continue;
        dfs(v, u);
        for (int ku = K; ku >= 0; ku--)
        {
            for (int kv = 0; kv <= ku; kv++)
            {
                dp[u][ku][1] = max(dp[u][ku][1], dp[v][kv][0] + dp[u][ku - kv][1]);
                dp[u][ku][0] = max(dp[u][ku][0], max(dp[v][kv][1], dp[v][kv][0]) + dp[u][ku - kv][0]);
                // state 1 is the node is selected, 0 is not selecting that node
            }
        }
    }
}
signed main(void)
{
    cin >> n >> K;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> b[i];
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    cout << max(dp[1][K][1], dp[1][K][0]) << '\n';
    return 0;
}