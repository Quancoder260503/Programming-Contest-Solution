#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int MAXN = 2e3 + 10;
const int M = 30;
lint dp[M][MAXN];
int n, k, q;
int cnt[MAXN][26];
int target[26];
signed main(void)
{
    cin >> n >> q;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); j++)
        {
            if (65 <= s[j] && s[j] <= 90)
            {
                cnt[i][s[j] - 'A'] |= 1;
            }
        }
    }
    for (int i = 0; i < q; i++)
    {
        memset(dp, 0, sizeof(dp));
        string s;
        cin >> s;
        if (s.length() != n)
        {
            puts("0");
            continue;
        }
        int N = s.length();
        dp[0][0] = 1;
        for (int ch = 1; ch <= N; ch++)
        {
            for (int mask = 0; mask < (1 << n); mask++)
            {
                for (int at = 0; at < n; at++)
                {
                    if (mask & (1 << at))
                    {
                        dp[ch][mask] += 1LL * dp[ch - 1][mask xor (1 << at)] * cnt[at][s[ch - 1] - 'A'];
                    }
                }
            }
        }
        cout << dp[N][(1 << n) - 1] << '\n';
    }
    return 0;
}