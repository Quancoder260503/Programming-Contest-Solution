#include "bits/stdc++.h"
using namespace std; 
#define lint long long
lint ans, n; 
map<lint,lint>dp;
lint solve(lint n)
{
     if(n == 0) return 0; 
     if(dp[n]) return dp[n];
     if(n & 1)
     {
         return dp[n] = 2 * solve(n / 2) + (n / 2) + 1;
     }
     else 
     {
        return dp[n] = solve(n / 2) + solve(n / 2 - 1) + n / 2;
     }
}
signed main(void)
{
    cin >> n; 
    cout << solve(n) << endl;   
    return 0; 
}