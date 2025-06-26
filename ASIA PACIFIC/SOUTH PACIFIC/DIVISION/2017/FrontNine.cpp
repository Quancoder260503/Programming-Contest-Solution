#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e5 + 10;
double dp[MAXN][200];
int n, s, h;
double P[3];
double state[3] = {-1, 0, 1};
double f(int pos, int height)
{
    if (pos > n) return 0;
    if (dp[pos][height] != 1e9) return dp[pos][height];
    double &res = dp[pos][height];
    res = 0;
    for (int i = 0; i < 3; i++)
    {
        int next_h = min(max(height + state[i], 0.0), h * 1.0);
        res += P[i] * (abs(1.0 * next_h - 1.0 * height) / 2.0 + min(1.0 * next_h, 1.0 * height) + f(pos + 1, next_h)) / 100.0;
    }
    return res;
}
signed main(void)
{
    cin >> n >> h >> s >> P[0] >> P[1] >> P[2];
    for (int i = 0; i < MAXN; i++)
    {
        for (int j = 0; j < 200; j++)
        {
            dp[i][j] = 1e9;
        }
    }
    double ans = f(1, s);
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}