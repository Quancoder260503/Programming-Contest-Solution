#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)1e6 + 10
#define pii pair<int, int>
#define mp make_pair
vector<int> adj[MAXN];
vector<int> tadj[MAXN];
int n;
bool vis[MAXN];
bool biparte = true;
int f[MAXN];
int col[MAXN];
void dfs(int u, bool a)
{
    vis[u] = 1;
    f[u] = a;
    for (int i = 0; i < (int)adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (!vis[v])
        {
            dfs(v, a xor 1);
        }
        else
        {
            if (f[v] == a)
            {
                biparte = false;
                break;
            }
        }
    }
}
int difcol(int c1, int c2)
{
    for (int i = 1; i <= 3; i++)
    {
        if (c1 != i && c2 != i)
        {
            return i;
        }
    }
    return 0;
}
void dfs2(int u, int curr)
{
    if(curr == -1)
    {
         if(!col[u])
         {
             col[u] = 1; 
         }
         if(u < n && !col[u + 1])
         {
             dfs2(u + 1, (int) tadj[u + 1].size() - 1); 
         }
         return;
    }
    int to = tadj[u][curr]; 
    if(!col[u])
    {
        col[u] = difcol(col[to], -1); 
    }
    bool good = (!col[to]); 
    if(!col[to])
    {
       if(tadj[to].size())
       {
          col[to] = difcol(col[u], col[tadj[to].back()]); 
       }     
       else 
       {
          col[to] = difcol(col[u], -1); 
       }
    }
    dfs2(u, curr - 1);
    if(good)
    {
       dfs2(to, tadj[to].size() - 1);
    }
    return;
}
signed main(void)
{
    scanf("%d", &n);
    int hiring = 0;
    int firing = 0;
    stack<pii> stk;
    for (int i = 1; i <= n; i++)
    {
        int fi, hi;
        scanf("%d %d", &fi, &hi);
        if (stk.size() && stk.top().first <= fi)
        {
            while (stk.size() && stk.top().first <= fi)
            {
                int v = stk.top().second;
                fi -= stk.top().first;
                tadj[v].push_back(i);
                adj[i].push_back(v);
                adj[v].push_back(i);
                stk.pop();
            }
        }
        if (stk.size() && fi > 0)
        {
            stk.top().first = stk.top().first - fi;
            int v = stk.top().second;
            tadj[v].push_back(i);
            adj[i].push_back(v);
            adj[v].push_back(i);
        }
        if (hi > 0)
        {
            stk.push(mp(hi, i));
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            dfs(i, 0);
        }
    }
    if (biparte)
    {
        int ans = 0;
        for(int i = 1; i <= n; i++)
        {
            col[i] = f[i] + 1;
            ans = max(ans, f[i] + 1); 
        }
        printf("%d\n", ans); 
    }
    else
    {
        printf("3\n");
        dfs2(1, tadj[1].size() - 1); 
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", col[i]);
    }
    return 0;
}