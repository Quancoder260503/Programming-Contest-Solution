#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)200
#define INF (int)1e7;
int dp[MAXN][MAXN][2];
int n, m;
char s[MAXN];
int solve(int L, int R, int state)
{
    if (L >= R) return 0;
    if (dp[L][R][state] != -1) return dp[L][R][state];
    int res = solve(L + 2, R - 2, 0) + 2; 
    if(state || s[L] != s[R])
    {
        res = min(res, 1 + solve(L + 1, R - 1, 1)); 
    }
    if( (!state && s[L] == s[R]) || (state && s[L] != s[R]))
    {
         res = min(res, solve(L + 1, R - 1, 0)); 
    }
    return dp[L][R][state] = res;
}
signed main(void)
{
    cin >> s;
    n = strlen(s);
    memset(dp, -1, sizeof(dp));
    cout << solve(0, n - 1, 0) << '\n';
    return 0;
}
/*
  010  000 
  vetted
  011110 -> 111111 -> 2
*/