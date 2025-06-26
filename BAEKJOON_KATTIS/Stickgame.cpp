#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e6 + 10 
int n, k; 
int arr[MAXN]; 
bool dp[MAXN]; 
signed main(void)
{
    cin >> n >> k; 
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= k; i++)
    {
         cin >> arr[i]; 
         dp[arr[i]] = 1; 
    }
    for(int i = 1; i <= n; i++)
    {
         if(dp[i]) cout << 'W'; 
         else 
         {
             for(int j = 1; j <= k; j++)
             {
                 if(arr[j] > i) continue; 
                 dp[i] = dp[i] | (dp[i - arr[j]] == 0) ; 
             }
             if(dp[i]) cout << 'W'; 
             else cout << 'L'; 
         }
    }
    return 0; 
}