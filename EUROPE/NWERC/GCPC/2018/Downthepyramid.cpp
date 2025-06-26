#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10
int arr[MAXN];
int dp[MAXN]; 
int n;   
signed main(void)
{
     scanf("%d", &n); 
     for(int i = 1; i <= n; i++)
     {
         scanf("%d", arr + i); 
     }
     if(n == 1)
     {
         printf("%d\n", arr[1] + 1);
         return 0; 
     }
     dp[1] = arr[1];
     int sign = 1; 
     for(int i = 2; i <= n; i++)
     {
         if(i & 1) dp[i] = dp[i - 1] + arr[i];
         else dp[i] = dp[i - 1] - arr[i]; 
     }
     int currmax = INT_MIN; 
     int currmin = INT_MAX; 
     for(int i = 1; i <= n; i++)
     {
         if(!(i & 1)) currmax = max(currmax , dp[i]);
         else currmin = min(currmin, dp[i]); 
     }
     if(currmin < 0 || currmax > currmin + 1)
     {
         puts("0"); 
     }
     else
     {
         printf("%d\n", -max(0, currmax) + currmin + 1); 
     }
     return 0; 
}