#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int MAXN = 1e4;
const int M = 8;
int g[M][M];
int n, m;
int valid[M][MAXN];
lint dp[M][MAXN];
const int mod = 998244353;
vector<int> ter[MAXN];
signed main(void)
{
   cin >> n >> m;
   char ch;
   memset(g, -1, sizeof(g));
   int cnt = 0;
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < m; j++)
      {
         cin >> ch;
         cnt += (ch == '?');
         if (ch == '?')
            continue;
         g[i][j] = (ch == 'C' ? 0 : (ch == 'I' ? 1 : 2));
      }
   }
   int fmask = 1;
   for (int i = 0; i < m; i++)
   {
      fmask = fmask * 3;
   }
   for (int mask = 0; mask < fmask; mask++)
   {
      int f = mask;
      while (f)
      {
         ter[mask].push_back(f % 3);
         f = f / 3;
      }
      while (ter[mask].size() < m) ter[mask].push_back(0);
      reverse(ter[mask].begin(), ter[mask].end());
   }
   for (int i = 0; i < n; i++)
   {
      for (int mask = 0; mask < fmask; mask++)
      {
         int good = 1;
         for (int j = 0; j < m; j++)
         {
            if (g[i][j] != -1 && g[i][j] != ter[mask][j])
            {
               good = 0;
               break;
            }
         }
         valid[i][mask] = good;
         if (i == 0) dp[i][mask] = good;
         if (!good || i == 0) continue;
         for (int nmask = 0; nmask < fmask; nmask++)
         {
            if (!valid[i - 1][nmask]) continue;
            int good = 1;
            for (int j = 1; j < m; j++)
            {
               good = good & (!(!ter[mask][j] && !ter[nmask][j] && ter[nmask][j - 1] == 1 && ter[mask][j - 1] == 2));
               if(!good) break;
            }
            if (good)
            {
               dp[i][mask] = (dp[i - 1][nmask] + mod + dp[i][mask]) % mod;
            }
         }
      }
   }
   lint ans = 0;
   for (int i = 0; i < fmask; i++)
   {
      ans += dp[n - 1][i];
      ans %= mod;
   }
   lint res = 1;
   for (int i = 0; i < cnt; i++)
   {
      res = res % mod * 3 % mod;
   }
   res = (res - ans + mod) % mod;
   cout << res << '\n';
   return 0;
}
/*
   Count the number of matrix which doesnt satisfy the constraint
   C : 0, I : 1, P : 2
*/