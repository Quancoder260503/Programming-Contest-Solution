#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> table(n, vector<int>(m, 0));
    for (int i = 0; i < k; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        table[u][v] = 1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            table[i][j] += (i ? table[i - 1][j] : 0) + (j ? table[i][j - 1] : 0) - (i && j ? table[i - 1][j - 1] : 0);
        }
    }
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};
    auto chk = [&](int L)
    {
        vector<vector<int>> vis(n, vector<int>(m, 0));
        auto calc = [&](int r, int c, int r1, int c1)
        {
            return table[r1][c1] + (r && c ? table[r - 1][c - 1] : 0) - (r ? table[r - 1][c1] : 0) - (c ? table[r1][c - 1] : 0);
        };
        auto inside = [&](int r, int c)
        {
            return (0 <= r && r < n && 0 <= c && c < m && calc(r, c, r, c) == 0 && vis[r][c] == 0);
        };
        auto doit = [&](int sx, int sy)
        {
            if (calc(sx, sy, sx + L, sy + L)) return false;
            queue<pair<int, int>> q;
            q.push({sx, sy});
            vis[sx][sy] = 1;
            while (q.size())
            {
                auto [tx, ty] = q.front();
                q.pop();
                for (int k = 0; k < 4; k++)
                {
                    int px = tx + dx[k];
                    int py = ty + dy[k];
                    if (inside(px, py))
                    {
                        if (px + L < n && py + L < m && calc(px, py, px + L, py + L) == 0)
                        {
                            // cout << px << " " << py << '\n';
                            vis[px][py] = 1;
                            q.push({px, py});
                        }
                    }
                }
            }
            vector<vector<int>> dyn(n, vector<int>(m, 0));
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if (vis[i][j])
                    {
                        dyn[i][j]++;
                        if (i + L + 1 < n)
                            dyn[i + L + 1][j]--;
                        if (j + L + 1 < m)
                            dyn[i][j + L + 1]--;
                        if (i + L + 1 < n && j + L + 1 < m)
                            dyn[i + L + 1][j + L + 1]++;
                    }
                }
            }
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    dyn[i][j] += -(i && j ? dyn[i - 1][j - 1] : 0) + (i ? dyn[i - 1][j] : 0) + (j ? dyn[i][j - 1] : 0);
                }
            }
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    /// cout << i << " " << j << " " << dyn[i][j] << " " << calc(i, j, i, j) << '\n';
                    if (calc(i, j, i, j) == 0 && dyn[i][j] == 0)
                        return false;
                }
            }
            return true;
        };
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (calc(i, j, i, j))
                    continue;
                if (i + L < n && j + L < m)
                    return doit(i, j);
            }
        }
        return false;
    };
    int lo = 0;
    int hi = 1e7;
    while (lo < hi)
    {
        int mid = (lo + hi + 1) / 2;
        if (chk(mid))
        {
            lo = mid;
        }
        else
        {
            hi = mid - 1;
        }
    }
    cout << (chk(lo) ? lo + 1 : -1) << '\n';
    return 0;
}