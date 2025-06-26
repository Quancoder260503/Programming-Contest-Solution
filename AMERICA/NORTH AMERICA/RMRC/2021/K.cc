#include "bits/stdc++.h"
using namespace std;
const int INF = 1e9;
const int MAXN = 9000;
int M, N, Q, S, T;
string S1, S2;
vector<unordered_map<int, int>> g;
vector<int> par;
void init(int n) { g = vector<unordered_map<int, int>>(n); }
void add_edge(int u, int v, int c) { g[u][v] = c; }
int augment(int v, int pre, int t, int mn)
{
    if (v == t)
        return mn;
    if (par[v] != -1)
        return 0;
    par[v] = pre;

    for (auto &p : g[v])
    {
        if (p.second == 0)
            continue;
        int nxt = augment(p.first, v, t, min(mn, p.second));
        if (nxt)
        {
            p.second -= nxt;
            g[p.first][v] += nxt;
            return nxt;
        }
    }
    return 0;
}  
void mincut(int s, int t)
{
    do
    {
        par.assign(g.size(), -1);
    } 
    while (augment(s, -2, t, INF));
}
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> N >> M >> S1 >> S2)
    {
        S = 2 * N;
        T = 2 * N + 1;
        init(2 * N + 2);
        for (int i = 0; i < N; i++)
        {
            add_edge(i, N + i, 1);
            if (S2[i] == '?')
                continue;
            if (S1[i] == S2[i])
                add_edge(S, i, 2);
            else
                add_edge(i + N, T, 2);
        }
        for (int i = 0; i < M; i++)
        {
            int U, V;
            cin >> U >> V;
            --U, --V;
            add_edge(U + N, V, 2);
            add_edge(V + N, U, 2);
        }
        string ret;
        mincut(S, T);
        for (int i = 0; i < N; i++)
        {
            if (par[N + i] != -1)
                ret += S1[i];
            else if (par[i] != -1)
                ret += 'X';
            else
                ret += (S1[i] == 'A' ? 'B' : 'A');
        }
        cout << ret << '\n';
    }
    return 0;
}