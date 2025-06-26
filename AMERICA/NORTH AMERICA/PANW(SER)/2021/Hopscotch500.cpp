#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define pii pair<lint, lint>
#define mp make_pair
const int MAXN = (int)600;
const int M = (int) 3e5 + 10; 
vector<pii> adj[M];
int n, k;
lint dp[MAXN][MAXN];
int a[MAXN][MAXN];
signed main(void)
{
    cin >> n >> k;
    memset(dp, 63, sizeof(dp));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> a[i][j];
            adj[a[i][j]].push_back(mp(i, j));
            if (a[i][j] == 1)
                dp[i][j] = 0;
        }
    }
    for (int i = 1; i < k; i++)
    {
        vector<pii> R(n + 1, mp((lint)1e12, -1));
        vector<pii> C(n + 1, mp((lint)1e12, -1));
        for (int j = 0; j < adj[i].size(); j++)
        {
            auto curr = adj[i][j];
            R[curr.first] = min(R[curr.first], mp(dp[curr.first][curr.second], curr.second));
            C[curr.second] = min(C[curr.second], mp(dp[curr.first][curr.second], curr.first));
        }
        for (int j = 0; j < adj[i + 1].size(); j++)
        {
            auto curr = adj[i + 1][j];
            for (int p = 1; p <= n; p++)
            {
                if (R[p].first < (lint)1e12)
                {
                    lint dist = min(1LL * (R[p].second - curr.second) * (R[p].second - curr.second), 1LL * (p - curr.first) * (p - curr.first));
                    dp[curr.first][curr.second] = min(dp[curr.first][curr.second], R[p].first + dist);
                }
                if (C[p].first < (lint)1e12)
                {
                    lint dist = min(1LL * (C[p].second - curr.first) * (C[p].second - curr.first), 1LL * (p - curr.second) * (p - curr.second));
                    dp[curr.first][curr.second] = min(dp[curr.first][curr.second], C[p].first + dist);
                }
            }
        }
    }
    lint ans = (lint) 1e12;
    for(int i = 0; i < adj[k].size(); i++)
    {
         auto curr = adj[k][i]; 
         ans = min(ans, dp[curr.first][curr.second]); 
    }
    cout << (ans >= (lint) 1e12 ? -1 : ans) << '\n'; 
    return 0;
}