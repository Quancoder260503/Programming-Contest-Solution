#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#define blksz 500
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 10002;
const int M = 24;
long long dp[N];
int fa[N];
bool vis[N];
long long A[N];
int deg[N];
vector<pii> adj[N];
int n, m;
long long DP(int u)
{
    if (dp[u])
        return dp[u];
    long long ans = 0;
    for (int i = 0; i < adj[u].size(); i++)
    {
        ans = max(ans, DP(adj[u][i].first) + adj[u][i].second);
    }
    return dp[u] = ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    // memset(dp,-1,sizeof(dp));
    for (int i = 0; i < m; ++i)
    {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        --u, --v;
        // adj[u].push_back({v,c});
        adj[v].push_back({u, c});
    }
    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans = max(ans, DP(i));
    }
    printf("%lld\n", ans);
    return 0;
}