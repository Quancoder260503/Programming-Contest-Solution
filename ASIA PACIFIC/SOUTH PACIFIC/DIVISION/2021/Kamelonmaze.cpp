#include "bits/stdc++.h"
using namespace std;
#define x first
#define y second
int n, m, K;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1};
queue<pair<int, int>> start;
pair<int, int> target;
bool calcC(vector<vector<int>> &table, int r, int L, int R)
{
    return (table[r][R] - (L == 0 ? 0 : table[r][L - 1])) == (r == 0 ? 0 : table[r - 1][R] - (L == 0 ? 0 : table[r - 1][L - 1]));
}
bool calcR(vector<vector<int>> &table, int c, int L, int R)
{
    return (table[R][c] - (L == 0 ? 0 : table[L - 1][c])) == (c == 0 ? 0 : table[R][c - 1] - (L == 0 ? 0 : table[L - 1][c - 1]));
}
void bfs(int at, vector<vector<vector<int>>> &opt, vector<vector<int>> &dp, vector<vector<char>> &g, vector<vector<int>> &table)
{
    using T = pair<int, pair<int, int>>;
    priority_queue<T, vector<T>, greater<T>> pq;
    while (start.size())
    {
        int px = start.front().x;
        int py = start.front().y;
        dp[px][py] = (at == 0 ? 0 : opt[px][py][at - 1]);
        pq.push({dp[px][py], {px, py}});
        start.pop();
    }
    while (pq.size())
    {
        int px = pq.top().y.x;
        int py = pq.top().y.y;
        int cost = pq.top().x;
        pq.pop();
        if (dp[px][py] != cost)
            continue;
        if (target.x == px && abs(target.y - py) <= K)
        {
            if (calcC(table, px, min(target.y, py), max(target.y, py)))
            {
                opt[px][py][at] = min(opt[px][py][at], dp[px][py] + 1);
            }
        }
        if (target.y == py && abs(target.x - px) <= K)
        {
            if (calcR(table, py, min(target.x, px), max(target.x, px)))
            {
                opt[px][py][at] = min(opt[px][py][at], dp[px][py] + 1);
            }
        }
        for (int k = 0; k < 4; k++)
        {
            int tx = dx[k] + px;
            int ty = dy[k] + py;
            if (tx < 0 || ty < 0 || tx >= n || ty >= m)
                continue;
            if (g[tx][ty] == '#')
                continue;
            if (dp[tx][ty] > dp[px][py] + 1)
            {
                dp[tx][ty] = dp[px][py] + 1;
                pq.push({dp[tx][ty], {tx, ty}});
            }
        }
    }
}
signed main(void)
{
    cin >> n >> m >> K;
    vector<vector<char>> g(n, vector<char>(m));
    vector<vector<int>> table(n, vector<int>(m));
    vector<vector<int>> dp(n, vector<int>(m));
    vector<vector<vector<int>>> opt(n, vector<vector<int>>(m, vector<int>(10, (1e9))));
    vector<pair<int, pair<int, int>>> to;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> g[i][j];
            if (isdigit(g[i][j]))
            {
                to.push_back({g[i][j] - '0', {i, j}});
                g[i][j] = '.';
            }
            if (g[i][j] == 'S')
            {
                start.push({i, j});
                g[i][j] = '.';
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            table[i][j] = (g[i][j] == '#');
            table[i][j] += (j > 0 ? table[i][j - 1] : 0);
            table[i][j] += (i > 0 ? table[i - 1][j] : 0);
            table[i][j] -= (i > 0 && j > 0 ? table[i - 1][j - 1] : 0);
        }
    }
    sort(to.begin(), to.end());
    int ans = (int)1e9;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            dp[i][j] = 1e9;
        }
    }
    for (int k = 0; k < to.size(); k++)
    {
        target = to[k].second;
        bfs(k, opt, dp, g, table);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (opt[i][j][k] < (int)1e9)
                {
                    start.push({i, j});
                }
                dp[i][j] = 1e9;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ans = min(ans, opt[i][j][8]);
        }
    }
    cout << ans << endl;
    return 0;
}