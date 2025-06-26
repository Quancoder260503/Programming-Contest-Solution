#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e5 + 10;
int dp[MAXN];
int n, m;
vector<int> adj[MAXN];
int bfs()
{
    queue<int> q;
    memset(dp, -1, sizeof(dp));
    dp[1] = 0;
    q.push(1);
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i];
            if (dp[v] == -1)
            {
                dp[v] = dp[u] + 1;
                q.push(v);
            }
        }
    }
    return dp[n] - 1;
}
signed main(void)
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int ans = bfs(); 
    cout <<  (ans < 0 ? -1 : ans) << '\n';
    return 0;
}