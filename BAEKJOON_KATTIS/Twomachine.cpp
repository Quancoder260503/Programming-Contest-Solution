#include "bits/stdc++.h" 
using namespace std;
const int N = 256;
const int M = 251;
const int inf = 1e7 + 5;
const int mod = 1e9 + 7;
int n, m, k, q, p, d;
long long dp[2][N * N + 2];
long long A[N + 1];
long long B[N + 1];
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> A[i] >> B[i];
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[1][0] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = N * N; j >= 0; j--)
        {
            dp[i & 1][j] = mod;
            dp[i & 1][j] = min(dp[i & 1][j], dp[(i + 1) & 1][j] + B[i]);
            if (j >= A[i])
            {
               dp[i & 1][j] = min(dp[i & 1][j], dp[(i + 1) & 1][j - A[i]]);
            }
        }
    }
    long long ans = INT_MAX;
    for (int i = 1; i <= N * N; i++)
    {
        ans = min(ans, max(1LL * i, dp[(n - 1) & 1][i]));
    }
    cout << ans << '\n';
    return 0;
}