#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 2e4 + 5
#define mp make_pair
#define M 510
string s[M];
int n, m;
int dp[M][MAXN];
int ans[MAXN];
signed main(void)
{
     cin >> n >> m;
     for (int i = 1; i <= n; i++)
     {
          cin >> s[i]; 
     }
     for(int i = 0; i < MAXN; i++)
     {
          for(int j = 0; j < M; j++)
          {
               dp[j][i] = INT_MAX;
          }
     }
     for (int i = 1; i < n; i++)
     {
          for (int j = m - 1; j >= 0; j--)
          {
               if (s[i][j] < s[i + 1][j])
               {
                    dp[i][j] = 1;
               }
               else if (s[i][j] == s[i + 1][j] && dp[i][j + 1] != INT_MAX)
               {
                    dp[i][j] = dp[i][j + 1] + 1;
               }
          }
     }
     int pos = 0;
     for (int i = 0; i < m; i++)
     {
          for (int j = 1; j < n; j++)
          {
               ans[i] = max(ans[i], dp[j][i]);
          }
          if(ans[pos] > ans[i])
          {
               pos = i;
          }
     }
     cout << pos + 1 << " " << pos + ans[pos] << endl; 
     return 0;
}