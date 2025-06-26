#include "bits/stdc++.h"
using namespace std;
#define MAXN 200
#define pii pair<int, int>
#define mp make_pair
char g[MAXN][MAXN]; 
int dp[MAXN][MAXN][4];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int n;
void bfs(int tx, int ty)
{
    using T = pair<pii, pii>; 
    priority_queue<T, vector<T>, greater<T> > pq; 
    for (int k = 0; k < 4; k++)
    {
        pq.push(mp(mp(0, k), mp(tx, ty)));
        dp[tx][ty][k] = 0; 
    }
    while(pq.size())
    {
         int w =   pq.top().first.first;
         int dir = pq.top().first.second; 
         int px =  pq.top().second.first; 
         int py =  pq.top().second.second; 
         pq.pop(); 
         if(dp[px][py][dir] != w) continue;
         for(int k = 0; k < 4; k++)
         {
             int kx = px + dx[k];
             int ky = py + dy[k]; 
             if(kx > n || ky > n || kx < 1 || ky < 1) continue; 
             if(g[kx][ky] == '#') continue; 
             int cost = (dir != k); 
             if(dp[kx][ky][k] > dp[px][py][dir] + cost)
             {
                 dp[kx][ky][k] = dp[px][py][dir] + cost; 
                 pq.push(mp(mp(dp[kx][ky][k], k), mp(kx, ky))); 
             }
         }
    }
    return; 
}
signed main(void)
{
    cin >> n; 
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cin >> g[i][j]; 
        }
    }
    memset(dp, 63, sizeof(dp)); 
    bfs(1, 1);
    cout << min(dp[n][n][0], min(dp[n][n][1], min(dp[n][n][2], dp[n][n][3]))) + 1 << '\n'; 
    return 0;
}