#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e3 + 10;
int n, m, K;
#define lint long long
int g[MAXN][MAXN];
lint dp[MAXN][MAXN];
pair<int, bool> fa[MAXN][MAXN];
lint tot[MAXN][MAXN];
signed main(void)
{
    cin >> n >> m >> K;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> g[i][j];
            tot[i][j] += g[i][j] + tot[i][j - 1];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j + K <= m + 1; j++)
        {
            for (int k = j; k <= j + K - 1; k++)
            {
                if (dp[i][j] < dp[i - 1][k] + tot[i][j + K - 1] - tot[i][j - 1])
                {
                    dp[i][j] = dp[i - 1][k] + tot[i][j + K - 1] - tot[i][j - 1];
                    fa[i][j] = {k, 0};
                }
            }
        }
        for (int j = m; j - K >= 0; j--)
        {
            for (int k = j; k >= j - K + 1; k--)
            {
                if (dp[i][j] < dp[i - 1][k] + tot[i][j] - tot[i][j - K])
                {
                    dp[i][j] = dp[i - 1][k] + tot[i][j] - tot[i][j - K];
                    fa[i][j] = {k, 1};
                }
            }
        }
    }
    pair<lint, pair<int, int>> ans;
    for (int i = 1; i <= m; i++)
    {
        ans = max(ans, {dp[n][i], {n, i}});
    }
    vector<vector<char>> res;
    for (int i = 1; i <= n; i++)
    {
        auto [x, k] = ans.second;
        auto [f, sign] = fa[x][k];
        vector<char> ch;
        if (!sign)
        {
            for (int j = 1; j < k; j++)
            {
                ch.push_back('.');
            }
            for (int j = k; j < k + K; j++)
            {
                ch.push_back('X');
            }
            for (int j = k + K; j <= m; j++)
            {
                ch.push_back('.');
            }
        }
        else
        {
            for (int j = 1; j <= k - K; j++)
            {
                ch.push_back('.');
            }
            for (int j = k - K + 1; j <= k; j++)
            {
                ch.push_back('X');
            }
            for (int j = k + 1; j <= m; j++)
            {
                ch.push_back('.');
            }
        }
        ans.second.first--;
        ans.second.second = f;
        res.push_back(ch);
    }
    reverse(res.begin(), res.end());
    for (auto row : res)
    {
        for (auto ch : row)
        {
            cout << ch;
        }
        cout << '\n';
    }
    return 0;
}