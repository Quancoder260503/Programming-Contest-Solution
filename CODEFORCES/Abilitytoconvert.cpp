#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 100
#define LIM 11
#define lint long long
lint dp[MAXN][MAXN]; 
int n, base; 
string s; 
lint binpow(lint a, int pow)
{
     lint ans = 1; 
     while(pow)
     {
         if(pow & 1)
         {
             if(a < 0)
             {
                 return (lint) 1e18 + 1;
             }
             ans = ans * a;
         }
         a = a * a; 
         pow = pow / 2;
     }
     return ans;
}
lint convert(int j, int i)
{
     lint pow = 1;
     lint ans = 0; 
     if(s[i] == '0')
     {
        return i == j ? 0 : base + 1; 
     }
     for(int k = j; k <= i; k++)
     {
         ans += (s[k] - '0') * pow;
         pow = pow * 10; 
     }
     return ans;
}
signed main(void)
{
     cin >> base >> s;
     int n = s.length();
     reverse(s.begin(), s.end());
     s = " " + s;   
     memset(dp, 63, sizeof(dp)); 
     dp[0][0] = 0; 
     for(int k = 1; k <= n; k++)
     { 
         if(binpow(base, k - 1) > (lint) 1e18) break;
         for(int i = 1; i <= n; i++)
         {
             for(int j = i; j > 0 && i - j + 1 < LIM; j--)
             {
                 lint opt = convert(j, i); 
                 if(opt < 1LL * base)
                 {
                     if(dp[j - 1][k - 1] + 1LL * binpow(base,k - 1) * opt < 0) continue; 
                     dp[i][k] = min(dp[j - 1][k - 1] + 1LL * binpow(base, k - 1) * opt, dp[i][k]); 
                 }
             }
         }
     } 
     lint ans = (lint) 1e18;
     for(int i = 1; i <= n; i++)
     {
        ans = min(ans, dp[n][i]); 
     }
     cout << ans << '\n'; 
     return 0;
}