#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)3e5 + 10
#define mp make_pair
#define pii pair<int, int>
vector<int> adj[MAXN];
int n, m;
int timer = 1;
set<int> dep[MAXN];
int dp[MAXN];
int in[MAXN], out[MAXN];
int tree[MAXN * 4] = {0};
int lazy[MAXN * 4] = {0};
int fa[MAXN];
void dfs(int u, int d)
{
    dp[u] = d;
    in[u] = timer++;
    sort(adj[u].begin(), adj[u].end()); 
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        fa[v] = u;
        dfs(v, d + 1);
    }
    out[u] = timer - 1;
    return;
}
bool inside(int root, int u)
{
    return in[root] <= in[u] && in[u] <= out[root];
}
signed main(void)
{
    cin >> n >> m;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    int ans = 1;
    dfs(1, 0); 
    int now;
    cin >> now; 
    for (int i = 1; i < m; i++)
    {
        int x; cin >> x; 
        if(in[x] >= in[now] || inside(x, now))
        {
             if(in[x] >= in[now])
             {
                now = x; 
             }
             ans++; 
        }
        else 
        {
            break; 
        }
    }
    cout << ans << '\n';
    return 0;
}
/*
  The road closed down will not be able for future people
  Greedy close the road
*/