#include "bits/stdc++.h"
using namespace std;
const int MAXN = 3000;
#define x first
#define y second
pair<double, double> point[MAXN];
pair<double, double> start, en;
double dist[MAXN][MAXN];
int n;
vector<int> tram[MAXN];
map<pair<double, double>, int> mp;
vector<pair<double, double>> adj[MAXN];
double calc_dist(int u, int v)
{
    return sqrt((double)((point[u].x - point[v].x) * (point[u].x - point[v].x) + (point[u].y - point[v].y) * (point[u].y - point[v].y)));
}
signed main(void)
{
    cin >> point[0].x >> point[0].y >> point[201].x >> point[201].y >> n;
    int N = 1;
    for (int i = 1; i <= n; i++)
    {
        int u, v;
        while (true)
        {
            cin >> u >> v;
            if (u == -1 && v == -1)
                break;
            tram[i].push_back(N);
            point[N] = {u, v};
            N++;
        }
    }
    point[N] = point[201];
    for (int i = 0; i < MAXN; i++)
    {
        for (int j = 0; j < MAXN; j++)
        {
            dist[i][j] = 1e9;
        }
    }
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            dist[i][j] = min(dist[i][j], calc_dist(i, j) / 166.667);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j + 1 < tram[i].size(); j++)
        {
            int u = tram[i][j];
            int v = tram[i][j + 1];
            dist[u][v] = min(dist[u][v], calc_dist(u, v) / 666.667);
            dist[v][u] = min(dist[v][u], calc_dist(v, u) / 666.667);
        }
    }
    for (int k = 0; k <= N; k++)
    {
        for (int i = 0; i <= N; i++)
        {
            for (int j = 0; j <= N; j++)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    cout << round(dist[0][N]) << endl;
    return 0;
}
