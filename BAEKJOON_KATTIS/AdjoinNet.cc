#include "bits/stdc++.h"

using namespace std;
const int maxf = 1e6 + 2;
const int INF = 1e9;

vector<int> g[maxf];
int vis[maxf], dist[maxf];
vector<int> cc[maxf];
int ctr = 0;

void dfs(int u, int p)
{
    vis[u] = 1;
    cc[ctr].push_back(u);
    for (auto v : g[u])
        if (v != p)
        {
            dfs(v, u);
        }
    return;
}

void dfs2(int u, int p)
{
    for (auto v : g[u])
        if (v != p)
        {
            dist[v] = dist[u] + 1;
            dfs2(v, u);
        }
    return;
}

int main(void)
{
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int U, V;
        cin >> U >> V;
        g[U].push_back(V);
        g[V].push_back(U);
    }
    vector<int> dia;
    int ret = 0;
    for (int i = 0; i < N; i++)
        if (!vis[i])
        {
            dfs(i, -1);
            dfs2(i, -1);
            sort(cc[ctr].begin(), cc[ctr].end(), [&](int i, int j) { return dist[i] < dist[j]; });
            int c = cc[ctr].back();
            dist[c] = 0;
            dfs2(c, -1);
            sort(cc[ctr].begin(), cc[ctr].end(), [&](int i, int j) { return dist[i] < dist[j]; });
            c = cc[ctr].back();
            ret = max(ret, dist[c]);
            dia.push_back((dist[c] + 1) / 2); 
            ctr++;
        }
    sort(dia.begin(), dia.end());
    if (dia.size() > 1)
    {
        ret = max(ret, dia.back() + 1 + dia[dia.size() - 2]);
    }
    if (dia.size() > 2)
    {
        ret = max(ret, dia[dia.size() - 2] + 2 + dia[dia.size() - 3]);
    }
    cout << ret << '\n';
    return 0;
}