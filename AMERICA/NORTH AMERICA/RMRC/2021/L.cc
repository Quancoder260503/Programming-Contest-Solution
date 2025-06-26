#include "bits/stdc++.h"
using namespace std;
#define double long double
const int MAX = 1e5 + 2;
int vis[MAX];
vector<int> adj[MAX];
void doit(int u, int &ctr)
{
    ctr++;
    vis[u] = 1;
    for (auto v : adj[u]) if (!vis[v])
    {
        doit(v, ctr);
    }
}
int main(void)
{
    int N, M;
    while (cin >> N >> M)
    {
        int64_t num = 0;
        for (int i = 0; i < M; i++)
        {
            int U, V;
            cin >> U >> V;
            adj[U].push_back(V);
            adj[V].push_back(U);
        }
        int ctr; 
        for (int i = 1; i <= N; i++) if (!vis[i])
        {
            ctr = 0;
            doit(i, ctr);
            num += 1LL * (ctr - 1) * ctr / 2;
        }
        int64_t den = 1LL * N * (N - 1) / 2;
        double ret = 1.0 * num / den; 
        cout << fixed << setprecision(10) << ret << '\n';
    }
    return 0;
}
/*
   Becareful of Integer overflow 
*/