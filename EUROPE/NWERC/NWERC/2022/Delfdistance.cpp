#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 2e6 + 10
#define M 800
#define mp make_pair
#define pid pair<int,double>
char g[M][M]; 
int n, m; 
vector<pid>adj[MAXN]; 
const double pi = acos(-1) / 2.0; 
double dist[MAXN]; 
pid fa[MAXN]; 
void djsktra()
{
   using T = pair<double, int>;
   fill(dist, dist + MAXN, 1e9); 
   priority_queue<T, vector<T>, greater<T> > pq;
   pq.push(mp(0,0));
   dist[0] = 0;
   while(pq.size())
   {
        int node = pq.top().second;
        double val = pq.top().first;
        pq.pop(); 
        if(val != dist[node]) continue; 
        for(int i = 0; i < (int) adj[node].size(); i++)
        {
            double weight = adj[node][i].second; 
            int v = adj[node][i].first;
            //if (v == 1538) cout << node << " " << dist[node] + weight << endl;
            if(dist[v] > dist[node] + weight)
            {
                 dist[v] = dist[node] + weight; 
                 fa[v] = mp(node, weight);
                 pq.push(mp(dist[v], v)); 
            }
        }
   }
}
int hsh(int tx, int ty, int cm)
{
    return cm * tx + ty; 
}
signed main(void)
{
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
         for(int j = 1; j <= m; j++)
         {
             scanf(" %c", &g[i][j]);
         }
    }
    int cn = 2 * n + 1; 
    int cm = 2 * m + 1; 
    for(int i = 0; i < cm * cn; i++)
    {
        if((i + 1) % cm == 0) continue; 
        int curx = i / cm;
        if(curx % 2 == 0)
        {
            adj[i].push_back(mp(i + 1, 5.0));
            adj[i + 1].push_back(mp(i, 5.0));
        }
    }
    for(int i = 0; i < cm * cn; i++)
    {
        if(i + cm < cn * cm)
        {
            int cury = i % cm;
            if(cury & 1) continue;
            adj[i].push_back(mp(i + cm, 5.0));
            adj[i + cm].push_back(mp(i, 5.0));
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(g[i][j] == 'X') continue;
            int u = hsh(2 * i - 2, 2 * j - 1, cm); 
            int v = hsh(2 * i - 1, 2 * j , cm);
            adj[u].push_back(mp(v, pi * 5.0));
            adj[v].push_back(mp(u, pi * 5.0));
            v = hsh(2 * i - 1, 2 * j - 2, cm);
            adj[u].push_back(mp(v, pi * 5.0));
            adj[v].push_back(mp(u, pi * 5.0));
            u = hsh(2 * i, 2 * j - 1, cm);
            adj[u].push_back(mp(v, pi * 5.0));
            adj[v].push_back(mp(u, pi * 5.0));
            v = hsh(2 * i - 1, 2 * j, cm);
            adj[u].push_back(mp(v, pi * 5.0));
            adj[v].push_back(mp(u, pi * 5.0));
        }
    }
    djsktra();
    printf("%.15f\n", dist[cn * cm - 1]); 
    int cur = cn * cm  - 1; 
    return 0; 
}
/*
XXXOXXXXO
XOOXOXOOO
OOXXXXXXO
OXOOXOXOX

*/