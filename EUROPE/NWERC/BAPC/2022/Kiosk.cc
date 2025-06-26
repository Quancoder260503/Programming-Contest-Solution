#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e4;
const int INF = 1e9;

int N, M, a[maxf][maxf], d[maxf][maxf];

int main(void)
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            cin >> a[i][j];
        }
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};
    auto idx = [&](int i, int j)
    { return i * M + j; };
    memset(d, -1, sizeof(d));
    auto bfs = [&](int sx, int sy)
    {
        int val = a[sx][sy];
        int src = idx(sx, sy);
        d[src][src] = 0;
        vector<vector<int>> g(N * M);
        for (int x = 0; x < N; x++)
            for (int y = 0; y < M; y++)
            {
                if (x == sx && y == sy)
                    continue;
                int kx = -1, ky = -1, dist = INF, dist2 = INF;
                for (int i = 0; i < 4; i++)
                {
                    int px = x + dx[i], py = y + dy[i];
                    if (0 <= px && px < N && 0 <= py && py < M)
                    {
                        if (dist > abs(val - a[px][py]) || dist == abs(val - a[px][py]) && dist2 > abs(a[x][y] - a[px][py]))
                        {
                            dist = abs(val - a[px][py]);
                            dist2 = abs(a[x][y] - a[px][py]);
                            kx = px, ky = py;
                        }
                    }
                }
                if (kx == -1 || ky == -1)
                    continue;
                g[idx(kx, ky)].push_back(idx(x, y));
            }
        function<void(int)> doit = [&](int u) -> void
        {
            for (auto v : g[u])
            {
                d[src][v] = d[src][u] + 1;
                doit(v);
            }
            return;
        };
        doit(idx(sx, sy));
        return;
    };
    for (int x = 0; x < N; x++)
        for (int y = 0; y < M; y++)
        {
            bfs(x, y);
        }
    pair<int, int> ret = {INF, -1};
    for (int x = 0; x < N * M; x++)
    {
        int sum = 0;
        int chk = 1;
        for (int y = 0; y < N * M; y++)
        {
            chk = chk & (d[y][x] + 1 > 0);
            sum = max(sum, d[y][x]);
        }
        if (ret.first > sum && chk)
        {
            ret.first = sum;
            ret.second = a[x / M][x % M];
        }
    }
    if(ret.first == INF) cout << "impossible" << '\n';
    else cout << ret.second << " " << ret.first << '\n'; 
    return 0;
}