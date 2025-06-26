#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)3e5 + 10
#define lint long long
#define ldb long double
#define pii pair<int,int>
#define mp make_pair
vector<int> adj[MAXN];
int dep[MAXN];
int n, m, q;
vector<int> comp[MAXN];
bool vis[MAXN];
int fa[MAXN];
vector<lint> sdep[MAXN];
vector<int> cdep[MAXN];
int dia[MAXN];
map<pii, double>dist;
void dfs(int u, int p, int curr)
{ 
    vis[u] = 1; 
    fa[u] = curr;
    comp[curr].push_back(u);
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == p)
            continue;
        dep[v] = dep[u] + 1;
        dfs(v, u, curr);
    }
}
void dfs1(int u, int p)
{ 
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        dfs1(v, u);
    }
}
int dfs2(int u, int p, int f, int dist)
{
    int curr = 0;
    dep[u] = max(dep[u], dist);
    cdep[f].push_back(dep[u]);
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == p) continue;
        curr = max(curr, 1 + dfs2(v, u, f, dist + 1));
    }
    return curr;
}
bool cmp(const int &a, const int &b)
{
    return dep[a] < dep[b];
}
signed main(void)
{
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int sz = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            dfs(i, 0, ++sz);
        }
    }
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= sz; i++)
    {
        int curr = comp[i].size();
        sort(comp[i].begin(), comp[i].end(), cmp);
        int far = comp[i][curr - 1];   
        dep[far] = 0; 
        dfs1(far, -1);
        sort(comp[i].begin(), comp[i].end(), cmp); 
        far = comp[i][curr - 1];  
        dia[i] = dfs2(far, -1, i, 0);
        sort(cdep[i].begin(), cdep[i].end());
        lint tot = 0;
        for (int j = 0; j < curr; j++)
        {
            tot += cdep[i][j];
            sdep[i].push_back(tot);
        }
    }
    for (int i = 0; i < q; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        if (fa[u] == fa[v])
        {
            puts("-1");
        }
        else
        {
            lint ans = 0;
            u = fa[u];
            v = fa[v];
            if (u > v)
                swap(u, v);
            if (dist.count(mp(u, v)))
            {
                printf("%.10lf\n", dist[mp(u, v)]);
                continue;
            }
            if (comp[u].size() > comp[v].size())
                swap(u, v);
            int curr = comp[v].size();
            for (int i = 0; i < comp[u].size(); i++)
            {
                int len = cdep[u][i];
                int pos = upper_bound(cdep[v].begin(), cdep[v].end(), max(dia[u], dia[v]) - len - 1) - cdep[v].begin();
                ans += 1LL * max(dia[u], dia[v]) * pos;
                if (pos == curr)
                    continue;
                ans += (len + 1) * (curr - pos) + (sdep[v][curr - 1] - (pos ? sdep[v][pos - 1] : 0));
            }
            double res = (double)ans / (double)(1LL * comp[u].size() * comp[v].size());
            if(u > v) swap(u, v); 
            dist[mp(u,v)] = res;
            printf("%.10lf\n", res);
        }
    }
    return 0;
}