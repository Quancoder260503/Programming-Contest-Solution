#include "bits/stdc++.h"
using namespace std;
#define x first
#define y second
const int M = 1002;
const int turn = 70;
int N;
int n;
vector<int> low, num, parent;
vector<bool> is_articulation;
int counter, root, children;
vector<pair<int, int>> bridges;
vector<int> articulation_points;
int64_t dist[M][M];
void dfs(int u, int64_t threshold)
{
    low[u] = num[u] = counter++;
    for (int v = 0; v < N; v++)
    {
        if (dist[u][v] <= threshold)
        {
            if (num[v] == -1)
            {
                parent[v] = u;
                dfs(v, threshold);
                if (low[v] >= num[u])
                    is_articulation[u] = true;
                low[u] = min(low[u], low[v]);
            }
            else if (v != parent[u])
                low[u] = min(low[u], num[v]);
        }
    }
}
bool f(int64_t threshold)
{
    fill(num.begin(), num.end(), -1);
    fill(low.begin(), low.end(), -1);
    fill(is_articulation.begin(), is_articulation.end(), 0);
    fill(parent.begin(), parent.end(), -1);
    counter = 0;
    dfs(N - 1, threshold);
    int ret = is_articulation[N - 1];
    for (int i = 0; i < N - 1; i++)
        ret = ret & (!is_articulation[i]);
    ret = ret & (counter == N);
    return ret;
}
signed main(void)
{
    while (cin >> N)
    {
        vector<pair<int64_t, int64_t>> P(N + 1);
        for (int i = 0; i < N; i++)
            cin >> P[i].x >> P[i].y;
        ++N;
        low.resize(N);
        parent.resize(N);
        num.resize(N);
        is_articulation.resize(N);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                dist[i][j] = (P[i].x - P[j].x) * (P[i].x - P[j].x) + (P[i].y - P[j].y) * (P[i].y - P[j].y);
            }
        for (int i = 0; i < N; i++)
            dist[i][i] = INT64_MAX;
        int64_t left = 0;
        int64_t right = 2e18; 
        for(int i = 0; i < turn; i++)
        {
            int64_t mid = (left + right) / 2;
            if(f(mid))
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        cout << fixed << setprecision(12) << sqrt(left) << '\n';
    }
    return 0;
}