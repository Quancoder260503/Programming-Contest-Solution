#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 2e3 + 10 
#define lint long long 
lint dp[MAXN][MAXN];
int n; 
int t[MAXN], c[MAXN]; 
lint f(int i, int j)
{
    if(j >= n) return 0;
    if(i > n) return (lint) 1e17; 
    if(dp[i][j]) return dp[i][j];  
    dp[i][j] = min(f(i + 1, j), f(i + 1, j + t[i] + 1) + c[i]); 
    return dp[i][j]; 
}
signed main(void)
{
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
         cin >> t[i] >> c[i]; 
    }
    cout << f(1, 0) << '\n'; 
    return 0;
}