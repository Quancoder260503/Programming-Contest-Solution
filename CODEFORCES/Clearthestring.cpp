#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)502
#define lint long long
lint dp[MAXN][MAXN];
char s[MAXN];
int n;
lint f(int L, int R)
{
    if (L > R) return 0;
    if (L == R) return 1;
    if (dp[L][R] != -1) return dp[L][R];
    lint ans =  1 + f(L + 1, R); 
    for(int i = L + 1 ; i <= R; i++)
    {
         if(s[L] == s[i]) ans = min(ans, f(L + 1, i - 1) + f(i, R)); 
    }
    return dp[L][R] = ans;
}
signed main(void)
{
    scanf("%d", &n);
    scanf(" %s", &s);
    memset(dp, -1, sizeof(dp)); 
    cout << f(0, n - 1) << "\n";
    return 0;
}
/*
    DP[i][j] = {min price to delete the string from i -> j }
 */