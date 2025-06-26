#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 2e3 + 10
int n, m;  
char g[MAXN][MAXN]; 
bool a[MAXN][MAXN]; 
bool vis[MAXN][MAXN]; 
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1}; 
void dfs(int i, int j)
{
     vis[i][j] = 1; 
     for(int k = 0; k < 4; k++)
     {
         int tx = dx[k] + i;
         int ty = dy[k] + j;
         if(tx < 0 || ty < 0 || tx > 2 * n + 1 || ty > 2 * m + 1) continue;
         if(vis[tx][ty] || a[tx][ty]) continue; 
         dfs(tx, ty); 
     }
}
signed main(void)
{
    cin >> n >> m;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
             cin >> g[i][j];
             if(g[i][j] == '.') continue;
             if(g[i][j] == '/')
             {
                 a[2 * i + 1][2 * j + 2] = 1; 
                 a[2 * i + 2][2 * j + 1] = 1; 
             }
             else
             {
                 a[2 * i + 2][2 * j + 2] = 1;
                 a[2 * i + 1][2 * j + 1] = 1;
             }
        }
    }
    int ans = 0; 
    for(int i = 0; i < 2 * n + 2; i++)
    {
         for(int j = 0; j < 2 * m + 2; j++)
         {
             if(!a[i][j] && !vis[i][j])
             {
                 dfs(i, j);
                 ans++; 
             }
         }
    }
    cout << ans - 1 << '\n'; 
    return 0; 
}