#include "bits/stdc++.h"
using namespace std;
#define MAXN 300
#define lint long long 
lint dp[MAXN][MAXN]; 
lint arr[MAXN]; 
int n, k; 
signed main(void)
{
    cin >> n >> k; 
    memset(dp, 63, sizeof(dp));
    for(int i = 1; i <= n; i++)
    {
         cin >> arr[i]; 
    }
    lint curmn = LLONG_MAX; 
    lint curmx = LLONG_MIN; 
    sort(arr + 1, arr + n + 1); 
    for(int i = 1; i <= n; i++)
    {
         curmn = min(curmn, arr[i]);
         curmx = max(curmx, arr[i]); 
         dp[i][1] = 1LL * (curmx - curmn) * (curmx - curmn); 
    }
    for(int i = 0; i <= k; i++)
    {
        dp[0][i] = 0; 
    }
    for(int i = 2; i <= k; i++)
    {
         for(int j = 1; j <= n; j++)
         {
             lint curmn = LLONG_MAX; 
             lint curmx = LLONG_MIN; 
             for(int p = j; p > 0; p--)
             {
                 curmn = min(curmn, arr[p]);
                 curmx = max(curmx, arr[p]); 
                 lint now = 1LL * (curmx - curmn) * (curmx - curmn); 
                 if(1LL * (now + dp[p - 1][i - 1]) < 0) continue;
                 dp[j][i] = min(dp[j][i], 1LL * (dp[p - 1][i - 1] + now)); 
             }
         }
    }
    cout << dp[n][k] << endl; 
    return 0; 
}