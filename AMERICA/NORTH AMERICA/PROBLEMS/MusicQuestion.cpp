#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e3 + 10
#define pii pair<int,int>
#define mp make_pair
bitset<MAXN>dp[2][MAXN];
int n, k; 
int arr[MAXN]; 
signed main(void)
{
      scanf("%d %d", &k, &n); 
      for(int i = 1; i <= n; i++)
      {
         scanf("%d", &arr[i]); 
      }
      dp[0][0][0] = 1;
      for(int i = 1; i <= n; i++)
      {
        for(int j = k; j >= 0; j--) 
        {
            dp[i & 1][j] |= (dp[(i + 1) & 1][j] << arr[i]);
            dp[i & 1][j] |= dp[(i + 1) & 1][j]; 
             if(j >= arr[i])
            {
               dp[i & 1][j] |= dp[(i + 1) & 1][j - arr[i]]; 
            }
        }
      }
      pii ans = mp(-1, -1); 
      for(int i = 0; i <= k; i++)
      {
         for(int j = 0; j <= k; j++)
         {
             if(dp[n & 1][i][j])
             {
                 if(ans.second + ans.first < i + j)
                 {
                    ans.first = max(i, j); 
                    ans.second = min(i, j); 
                 }
                 else if(ans.second + ans.first == i + j && ans.first - ans.second > abs(i - j))
                 {
                     ans.first = max(i, j); 
                     ans.second = min(i, j); 
                 }
             }
         }
      }
      printf("%d %d\n", ans.first, ans.second); 
      return 0; 
}