#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e6 + 10 
#define M 5000
#define pii pair<int,int> 
#define mp make_pair
int n, m;
char g[M][M]; 
char step[MAXN];
pii dxy[127];  
int dp[M][M]; 
int dp2[M][M]; 
bool vis[M][M]; 
char dir[4] = {'N', 'S', 'W', 'E'}; 
void bfs(pii s)
{
    queue<pair<int, pii> >q;
    q.push(mp(0, s)); 
    dp[s.first][s.second] = 0;
    vis[s.first][s.second] = 1;
    while(q.size())
    {
        pii at = q.front().second; 
        int dist = q.front().first;
        q.pop();
        if (dist == strlen(step)) continue;
        for(int i = 0; i < 4; i++)
        {
             if(dir[i] == step[dist]) continue;  
             int dx = dxy[dir[i]].first + at.first;
             int dy = dxy[dir[i]].second + at.second; 
             if(dx < 0 || dy < 0 || dx >= n || dy >= m) continue; 
             if(vis[dx][dy] || g[dx][dy] == '#') continue; 
             vis[dx][dy] = 1;
             dp[dx][dy] = 1 + dp[at.first][at.second];  
             q.push(mp(dp[dx][dy], mp(dx, dy)));  
        }
    }
}
void bfs2(pii s)
{
    queue<pair<int, pii> > q;
    q.push(mp(0, s));
    dp2[s.first][s.second] = 0;
    vis[s.first][s.second] = 1;
    while (q.size())
    {
        pii at = q.front().second;
        int dist = q.front().first;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
             int dx = dxy[dir[i]].first + at.first;
             int dy = dxy[dir[i]].second + at.second;
             if (dx < 0 || dy < 0 || dx >= n || dy >= m)
                 continue;
             if (vis[dx][dy] || g[dx][dy] == '#')
                 continue;
             vis[dx][dy] = 1;
             dp2[dx][dy] = 1 + dp2[at.first][at.second];
             q.push(mp(dp2[dx][dy], mp(dx, dy)));
        }
    }
}
signed main(void)
{
    scanf("%d %d", &m, &n);
    pii s;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
             scanf(" %c", &g[i][j]); 
             if(g[i][j] == 'S')
             {
                 s = mp(i, j); 
             }
        }
    } 
    scanf(" %s", &step); 
    dxy['N'] = mp(-1, 0); 
    dxy['S'] = mp(1, 0); 
    dxy['E'] = mp(0, 1); 
    dxy['W'] = mp(0, -1); 
    memset(dp, -1, sizeof(dp)); 
    bfs(s);
    memset(vis, 0, sizeof(vis));
    memset(dp2, -1, sizeof(dp2));
    bfs2(s); 
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
             if(dp[i][j] == dp2[i][j] && dp[i][j] == strlen(step) && g[i][j] == '.')
             {
                  g[i][j] = '!'; 
             }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
             printf("%c", g[i][j]); 
        }
        printf("\n"); 
    }
    return 0;
}