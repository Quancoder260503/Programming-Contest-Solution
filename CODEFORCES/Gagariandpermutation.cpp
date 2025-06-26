#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e3 + 10 
int n, m;
int a[MAXN][MAXN];  
int pos[MAXN][MAXN];
int dp[MAXN];  
signed main(void)
{ 
    cin >> n >> m;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
             cin >> a[i][j];
             pos[i][a[i][j]] = j;
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            int x = a[0][j], y = a[0][i];
            bool good = 1;  
            for(int k = 0; k < m; k++)
            {
                 good = good & (pos[k][x] < pos[k][y]); 
            }  
            if(good)
            {
                 dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    } 
    for(int i = 1; i < n; i++)
    {
         dp[i] = max(dp[i - 1], dp[i]); 
    }
    cout << dp[n - 1] + 1 << '\n'; 
    return 0; 
}
/*
    Target --> find LIS of five permutation 
   1 4 2 3 -> 1 3 4 2
   4 1 2 3 -> 2 3 4 1  
   1 2 4 3 -> 1 2 4 3 
*/