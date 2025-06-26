#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
const long long INF = 1e7 + 5;
const int mod = 1e9 + 7;
long long n, m, k, q, p;
vector<int> adj[N + 1];
set<int> dp[N + 1];
int a[N + 1];
long long mex[N + 1];
void dfs(int u)
{
    dp[u].insert(a[u]);
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        dfs(v);
        if (dp[v].size() > dp[u].size())
        {
            swap(dp[v], dp[u]);
        }
        for (auto it : dp[v])
        {
            dp[u].insert(it);
        }
    }
    if (*dp[u].begin() > 0)
    {
        mex[u] = 0;
        return;
    }
    auto it = dp[u].begin();
    if (dp[u].size() <= 1)
    {
        mex[u] = 1;
        return;
    }
    while (++it != dp[u].end())
    {
        auto pr = prev(it);
        if (*it - *pr > 1)
        {
            mex[u] = *pr + 1;
            return;
        }
    }
    mex[u] = *prev(dp[u].end()) + 1;
    return;
}
signed main()
{
    scanf("%d", &n);
    int s = 0;
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        if (x < 0) 
        {
            s = i;
            continue;
        }
        adj[x].push_back(i);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    dfs(s);
    for (int i = 1; i <= n; i++)
        printf("%lld\n", mex[i]);
    return 0;
}