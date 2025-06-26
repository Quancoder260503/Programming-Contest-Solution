#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)9e3 + 10;
int n, k, m;
double dp[MAXN][MAXN];
int t[MAXN];
double res[MAXN];
double prob[MAXN];
bool cmp(const int a, const int b)
{
    return t[a] < t[b];
}
signed main(void)
{
    cin >> n >> k >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> prob[i] >> t[i];
    }
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), cmp);
    dp[0][0] = 1.0;
    for (int i = 0; i < ord.size(); i++)
    {
        int at = ord[i];
        for (int j = k - 1; j >= 0; j--)
        {
            for (int p = 0; p <= m; p++)
            {
                if (p >= t[at])
                {
                    res[at] += prob[at] * dp[j][p - t[at]];
                    double c = 1.0 * (k - 1 - j) / (1.0 * (n - 1 - i));
                    dp[j + 1][p] += dp[j][p - t[at]] * prob[at] * c;
                    dp[j + 1][p - t[at]] += dp[j][p - t[at]] * c * (1.0 - prob[at]);
                    dp[j][p - t[at]] = dp[j][p - t[at]] * (1 - c);
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << setprecision(10) << res[i] << '\n';
    }
    return 0;
}