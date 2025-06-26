#include "bits/stdc++.h"

using namespace std;

struct UndirectedDfs
{
    vector<vector<int>> g;
    int n;
    vector<int> low, num, parent;
    vector<bool> is_articulation;
    int counter, root, children;

    vector<pair<int, int>> bridges;
    vector<int> articulation_points;
    map<pair<int, int>, int> cnt_edges;

    UndirectedDfs(const vector<vector<int>> &_g) : g(_g), n(g.size()),
                                                   low(n, 0), num(n, -1), parent(n, 0), is_articulation(n, false),
                                                   counter(0), children(0)
    {
        for (int u = 0; u < n; u++)
        {
            for (int v : g[u])
            {
                cnt_edges[{u, v}] += 1;
            }
        }
        for (int i = 0; i < n; ++i)
            if (num[i] == -1)
            {
                root = i;
                children = 0;
                dfs(i);
                is_articulation[root] = (children > 1);
            }
        for (int i = 0; i < n; ++i)
            if (is_articulation[i])
                articulation_points.push_back(i);
    }

private:
    void dfs(int u)
    {
        low[u] = num[u] = counter++;
        for (int v : g[u])
        {
            if (num[v] == -1)
            {
                parent[v] = u;
                if (u == root)
                    children++;
                dfs(v);
                if (low[v] >= num[u])
                    is_articulation[u] = true;
                if (low[v] > num[u])
                {
                    if (cnt_edges[{u, v}] == 1)
                    {
                        bridges.push_back(make_pair(u, v));
                    }
                }
                low[u] = min(low[u], low[v]);
            }
            else if (v != parent[u])
                low[u] = min(low[u], num[v]);
        }
    }
};

int N, M;

const int maxf = (1 << 18);

void FWHT(int64_t *P, int deg, bool invert, int mod, int inv)
{
    for (int len = 1; 2 * len <= deg; len = len * 2)
    {
        for (int i = 0; i < deg; i += 2 * len)
        {
            for (int j = 0; j < len; j++)
            {
                int64_t u = P[i + j];
                int64_t v = P[i + j + len];
                P[i + j] = (u + v) % mod;
                P[i + j + len] = (u - v + mod) % mod;
            }
        }
    }
    if (invert)
    {
        for (int i = 0; i < deg; i++)
        {
            P[i] = P[i] * inv % mod;
        }
    }
}

void conv(int64_t *a, int64_t *b, int deg, int mod, int inv)
{
    FWHT(a, deg, 0, mod, inv);
    FWHT(b, deg, 0, mod, inv);
    for (int i = 0; i < deg; i++)
        a[i] = a[i] * b[i] % mod;
    FWHT(a, deg, 1, mod, inv);
    FWHT(b, deg, 1, mod, inv);
    return;
}

int64_t a[maxf], a2[maxf], b[maxf];

const int mod  = 1000000007;
const int mod2 = 998244353;
const int inv = 742744451;
const int inv2 = 998236737;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    vector<vector<int>> g(N);
    vector<tuple<int, int, int>> edge;
    for (int i = 0; i < M; i++)
    {
        int U, V, W;
        cin >> U >> V >> W;
        --U, --V;
        edge.push_back({U, V, W});
        g[U].push_back(V);
        g[V].push_back(U);
    }
    UndirectedDfs dfs(g);
    set<pair<int, int>> s;
    for (auto [U, V] : dfs.bridges)
    {
        if (U > V) swap(U, V);
        s.insert({U, V});
    }
    vector<int> fa(N);
    iota(fa.begin(), fa.end(), 0);
    function<int(int)> find = [&](int u) -> int
    {
        return u == fa[u] ? u : fa[u] = find(fa[u]);
    };
    vector<vector<int>> h(N);
    int64_t ret = 0;
    for (auto [U, V, W] : edge)
    {
        if (U > V)
            swap(U, V);
        if (s.count({U, V}))
        {
            ret = ret xor W;
            continue;
        }
        U = find(U), V = find(V);
        if (h[U].size() > h[V].size())
            swap(U, V);
        h[V].push_back(W);
        if (U == V)
            continue;
        fa[U] = V;
        for (auto w : h[U])
            h[V].push_back(w);
        h[U].clear();
    }
    a[ret] = a2[ret] = 1;
    for (int i = 0; i < N; i++)
    {
        if (h[i].size())
        {
            memset(b, 0, sizeof(b));
            int64_t acc = 0;
            for (auto w : h[i])
                acc = acc xor w;
            for (auto w : h[i])
                b[w xor acc]++;
            conv(a, b, (1 << 17), mod, inv);
            conv(a2, b, (1 << 17), mod2, inv2);
        }
    }
    for (int i = 0; i < maxf; i++)
        if (a[i] || a2[i])
        {
            cout << i << " " << a[i] << '\n';
            break;
        }
    return 0;
}
#