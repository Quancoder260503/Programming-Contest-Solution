#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)4e5 + 10;
vector<vector<int> > adj;
int in[MAXN], low[MAXN], fa[MAXN];
bool vis[MAXN];
int deg[MAXN];
stack<int>stk;
int component;
vector<int> comp[MAXN];
vector<vector<int> > radj; 
int n, m;
int timer;
char ans[MAXN];
int cnt;
int flip(int x)
{
    return x xor 1;
}
void dfs(int u)
{  
    vis[u] = 1; 
    for(int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if(vis[v]) continue; 
        dfs(v); 
    }
    stk.push(u); 
    return;
}
void rdfs(int u)
{
    vis[u] = 1;
    fa[u] = component;
    for(int i = 0; i < radj[u].size(); i++) 
    {
        int v = radj[u][i]; 
        if(vis[v]) continue; 
        rdfs(v); 
    }
    return;
}
void solve()
{
    component = 0;
    fill(vis + 1, vis + 2 * n + 2, 0); 
    fill(fa + 1, fa + 2 * n + 2, 0); 
    adj.clear(); 
    adj.resize(2 * n + 2); 
    radj.clear();
    radj.resize(2 * n + 2);  
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        u = 2 * abs(u) + (u < 0);
        v = 2 * abs(v) + (v < 0);
        adj[flip(u)].push_back(v);
        adj[flip(v)].push_back(u);
        radj[u].push_back(flip(v));
        radj[v].push_back(flip(u)); 
    }
    for (int i = 1; i <= 2 * n + 1; i++)
    {
        if (!vis[i])
        {
            dfs(i);
        }
    }
    fill(vis + 1, vis + 2 * n + 2, 0); 
    while(stk.size())
    {
        int u = stk.top(); 
        stk.pop(); 
        if(!vis[u])
        {
            component++; 
            rdfs(u); 
        }
    }
    int good = 1; 
    for(int i = 1; i <= n; i++)
    {
        good = good & (fa[2 * i] != fa[2 * i + 1]);
    }
    if(good)
    {
        puts(fa[2] > fa[3] ? "yes" : "no"); 
    }
    else 
    {
        puts("no");
    }
    return;
}
signed main(void)
{
    while (cin >> n >> m)
    {
        cnt++;
        solve();
    }
    return 0;
}