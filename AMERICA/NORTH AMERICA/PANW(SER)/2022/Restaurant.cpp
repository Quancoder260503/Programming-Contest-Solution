#include "bits/stdc++.h"
using namespace std;
int g[51][51];
int n, m;
signed main(void)
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> g[i][j];
        }
    }
    auto dist = [&](int r, int c, int r2, int c2)
    {
        return abs(r - r2) + abs(c - c2);
    };
    int ans = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int now = 0;
            for (int f = 0; f < n; f++)
            {
                for (int s = 0; s < m; s++)
                {
                    now += dist(i, j, f, s) * g[f][s];
                }
            }
            ans = min(ans, now);
        }
    }
    cout << ans << '\n'; 
    return 0;
}