#include "bits/stdc++.h"
using namespace std;
#define pii pair<int,int>  
#define mp make_pair
#define x first
#define y second
#define MAXN (int) 1e4 + 10
#define lint long long
#define inf (lint) 1e17 + 10 
#define MAGIC 400
#define M 25 * 25 * 9
char c[MAXN][MAXN]; 
int n, m, r, s;
vector<pii>adj[MAXN];
double dp0[MAXN]; 
double dp[MAXN][MAXN];
int hsh(int i, int j)
{
    return (i - 1) * m + j; 
}
double dist(pii u, pii v)
{
     return hypot(u.first - v.first, u.second - v.second); 
}
double ldijsktra(pii src, pii dst,int lpower)
{
     using T = pair<double, pair<int, pii> >; 
     priority_queue<T, vector<T>, greater<T> > pq;
     for(int i = 0; i < MAXN; i++)
     {
             dp0[i] = 1e9; 
     }
     dp0[hsh(src.x, src.y)] = 0;
     pq.push(mp(0, mp(c[src.x][ src.y] - '0', src)));  
     while(pq.size())
     {
          double curr = pq.top().first; 
          int power = pq.top().second.first; 
          pii node = pq.top().second.second;
          pq.pop();
          int u = hsh(node.first, node.second);
          if(dp0[u] != curr) continue;
          for(int i = 0; i < adj[u].size(); i++)
          {
             pii curr = adj[u][i]; 
             int v = hsh(curr.x, curr.y); 
             int currpow = c[curr.x][curr.y] - '0'; 
             if(power + currpow <= lpower)
             {
                 if(dist(curr, node) + dp0[u] < dp0[v])
                 {
                     dp0[v] = dp0[u] + dist(curr, node); 
                     pq.push(mp(dp0[v], mp(power + currpow, curr))); 
                 }
             } 
          }    
     }
     double ans = 1e9;
     int dest = hsh(dst.x, dst.y);  
     for(int i = 0; i <= min(M, lpower); i++)
     {
         ans = min(ans, dp0[dest]); 
     }
     return ans;
}
double dijsktra(pii src, pii dst, int lpower)
{
     using T = pair<double, pair<int, pii> >;
     priority_queue<T, vector<T>, greater<T> > pq;
     for (int i = 0; i < MAXN; i++)
     {
         for (int j = 0; j < MAXN; j++)
         {
             dp[i][j] = 1e9;
         }
     }
     dp[hsh(src.x, src.y)][c[src.x][src.y] - '0'] = 0;
     pq.push(mp(0, mp(c[src.x][src.y] - '0', src)));
     while (pq.size())
     {
         double curr = pq.top().first;
         int power = pq.top().second.first;
         pii node = pq.top().second.second;
         pq.pop();
         int u = hsh(node.first, node.second);
         if (dp[u][power] != curr)
             continue;
         for (int i = 0; i < adj[u].size(); i++)
         {
             pii curr = adj[u][i];
             int v = hsh(curr.x, curr.y);
             int currpow = c[curr.x][curr.y] - '0';
             if (power + currpow <= lpower)
             {
                 if (dist(curr, node) + dp[u][power] < dp[v][power + currpow])
                 {
                     dp[v][power + currpow] = dp[u][power] + dist(curr, node);
                     pq.push(mp(dp[v][power + currpow], mp(power + currpow, curr)));
                 }
             }
         }
     }
     double ans = 1e9;
     int dest = hsh(dst.x, dst.y);
     for (int i = 0; i <= min(M, lpower); i++)
     {
         ans = min(ans, dp[dest][i]);
     }
     return ans;
}
signed main(void)
{
    scanf("%d %d %d %d", &n, &m, &r, &s);
    vector<pii>hold; 
    for(int i = 1; i <= n; i++)
    {
         for(int j = 1; j <= m; j++)
         {
             scanf(" %c", &c[i][j]);
             if(c[i][j] != '.')
             {
                 hold.push_back(mp(i, j)); 
             } 
         }
    }
    for(int i = 0; i < hold.size(); i++)
    {
         for(int j = i + 1; j < hold.size(); j++)
         {
             if(dist(hold[i], hold[j]) <= (double) r)
             {
                 int u = hsh(hold[i].x, hold[i].y);
                 int v = hsh(hold[j].x, hold[j].y); 
                 adj[u].push_back(hold[j]); 
                 adj[v].push_back(hold[i]); 
             }
         }
    }
    pii des = hold[0];
    pii src = hold[hold.size() - 1];
    double ans= hold.size() < MAGIC ? dijsktra(src, des, s) : ldijsktra(src, des, s); 
    if(ans == 1e9)
    {
         puts("impossible"); 
    }
    else
    {
         printf("%0.15lf\n",ans); 
    }
    return 0;
}