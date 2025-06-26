#include "bits/stdc++.h"
using namespace std; 
const int MAXN = (int) 3e5 + 10; 
#define lint long long 
lint dp[MAXN]; 
int n; 
int p[MAXN]; 
signed main(void)
{
    cin >> n; 
    memset(dp, -63, sizeof(dp)); 
    for(int i = 1; i <= n; i++)
    {
         cin >> p[i]; 
    }
    dp[1] = p[1]; 
    for(int j = n; j > 0; j--)
    {
         for (int i = 1; i <= n; i++)
         {
            if(i >= j) dp[i] = max(dp[i], dp[i - j] + p[i]);
         }
    }
    cout << dp[n] << '\n'; 
    return 0; 
}