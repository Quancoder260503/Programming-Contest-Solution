#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)5e4 + 10
#define M 52
#define mp make_pair
#define pii pair<int, int>
#define lint long long
int ADJ[M][M];
const int INF = 1e9;
vector<pii> adj[MAXN];
int n, m;
int fa[MAXN];
lint dp[M][MAXN];
signed main(void)
{
     cin >> m >> n;
     for (int i = 1; i <= m; i++)
     {
          cin >> fa[i];
     }
     for (int i = 1; i <= n; i++)
     {
          for (int j = 1; j <= n; j++)
          {
               char c; 
               cin >> c;
               ADJ[i][j] = c - '0';
          }
          ADJ[i][0] = ADJ[i][fa[m]];
     }
     memset(dp, -1, sizeof(dp));
     fa[m] = 0;
     dp[fa[1]][1] = 0;
     deque<pii> dq;
     dq.push_back(mp(fa[1], 1));
     while (dq.size())
     {
          int par = dq.front().first;
          int u = dq.front().second;
          dq.pop_front(); 
          if (u > 1 && dp[par][u - 1] == -1)
          {
               dp[par][u - 1] = dp[par][u] + 1;
               dq.push_back(mp(par, u - 1));
          }
          if (u < m && dp[par][u + 1] == -1)
          {
               dp[par][u + 1] = dp[par][u] + 1;
               dq.push_back(mp(par, u + 1));
          }
          if (ADJ[par][fa[u]] && dp[fa[u]][u] == -1)
          {
               dp[fa[u]][u] = dp[par][u];
               dq.push_front(mp(fa[u], u));
          }
     }
     cout << dp[0][m] << endl;
     return 0;
}