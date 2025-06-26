/* biparte matching */
#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)1e6 + 10
#define x first
#define y second
vector<int> adj[MAXN];
#define pii pair<int, int>
#define mp make_pair
int n, m;
int match[MAXN];
bool vis[MAXN];
pair<int, int> f[MAXN];
map<pair<int, int>, int> cor, col;
bool dfs(int u)
{
    if (vis[u])
        return false;
    vis[u] = true;
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (!match[v] || dfs(match[v]))
        {
            match[v] = u;
            return true;
        }
    }
    return false;
}
struct dice
{
    int xa, ya, xb, yb;
};
dice arr[MAXN];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
signed main(void)
{
    scanf("%d", &n);
    int sz = 0;
    for (int i = 1; i <= n; i++)
    {
        int xa, ya, xb, yb;
        scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
        if (!cor.count(mp(xa, ya)))
        {
            cor[mp(xa, ya)] = ++sz;
            f[sz] = mp(xa, ya);
        }
        if (!cor.count(mp(xb, yb)))
        {
            cor[mp(xb, yb)] = ++sz;
            f[sz] = mp(xb, yb);
        }
        arr[i].xa = xa;
        arr[i].ya = ya;
        arr[i].xb = xb;
        arr[i].yb = yb;
    }
    set<pii> edge;
    for (int i = 1; i <= n; i++)
    {
        bool odd = (arr[i].xa + arr[i].ya) % 2;
        for (int dir = 0; dir < 4; dir++)
        {
            if(!odd)
            {
                int tx = dx[dir] + arr[i].xa;
                int ty = dy[dir] + arr[i].ya;
                if (cor.count(mp(tx, ty)) && !(tx == arr[i].xb && ty == arr[i].yb))
                {
                    int v = cor[mp(tx, ty)];
                    int u = cor[mp(arr[i].xa, arr[i].ya)];
                    edge.insert(mp(u, v));
                }
            }
            else 
            {
                int tx = dx[dir] + arr[i].xb;
                int ty = dy[dir] + arr[i].yb;
                if (cor.count(mp(tx, ty)) && !(tx == arr[i].xa && ty == arr[i].ya))
                {
                    int v = cor[mp(tx, ty)];
                    int u = cor[mp(arr[i].xb, arr[i].yb)];
                    edge.insert(mp(u, v));
                }
            }
        }
    }
    for(auto it = edge.begin(); it != edge.end(); it++)
    {
         adj[it -> first].push_back(it -> second); 
    }
    for (int i = 1; i <= sz; i++)
    {
        fill(vis + 1, vis + sz + 1, false);
        dfs(i);
    }
    vector<pii> matches;
    for (int i = 1; i <= sz; i++)
    {
        if (match[i] == 0)
            continue;
        matches.push_back(mp(i, match[i]));
    }
    if (matches.size() == n)
    {
        int color = 0;
        for (int i = 0; i < matches.size(); i++)
        {
            pii curr = matches[i]; 
            if (!col.count(f[curr.x]) && !col.count(f[curr.y]))
            {
                col[f[curr.x]] = color;
                col[f[curr.y]] = color;
                color++;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            printf("%d %d\n", col[mp(arr[i].xa, arr[i].ya)], col[mp(arr[i].xb, arr[i].yb)]);
        }
    }
    else
    {
        puts("impossible");
    }
    return 0;
}