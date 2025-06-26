#include "bits/stdc++.h"

using namespace std;

const int maxf = 5e5 + 2;

map<vector<int>, int> mp;
map<int64_t, int> ctr;
int ctrsz[maxf];
int nodes = 1;

struct tree
{
    vector<vector<int>> g;
    vector<int> par, centroid;
    int n;
    tree(vector<vector<int>> &_g)
    {
        g = _g;
        n = g.size();
        par.resize(n);
    }
    int dfs(int u, int p)
    {
        vector<int> ret;
        for (auto v : g[u]) if (v != p) {
            ret.push_back(dfs(v, u));
        }
        sort(ret.begin(), ret.end());
        if (mp.count(ret) == 0) mp[ret] = nodes++;
        return mp[ret];
    }
    void dfs2(int u, int p)
    {
        par[u] = 1; 
        bool is_centroid = true; 
        for (auto v : g[u]) if (v != p) {
            dfs2(v, u);
            par[u] += par[v]; 
            if(par[v] > n / 2) is_centroid = false; 
        }
        if(n - par[u] > n / 2) is_centroid = false; 
        if(is_centroid) centroid.push_back(u); 
        return;
    }
    int64_t doit(void)
    {
        dfs2(0, -1); 
        int64_t a = dfs(centroid[0], -1);
        int64_t b = (centroid.size() > 1 ? dfs(centroid[1], -1) : -1);
        if(a > b) swap(a, b); 
        return (a << 30) + b;
    }
};

struct tree_t
{
    int n;
    vector<vector<int>> g;
    vector<pair<int, int>> edge;
    vector<int> root, vis, par;
    void input(int idx)
    {
        cin >> n;
        g.resize(n);
        vis.resize(n);
        par.resize(n);
        ctrsz[n]++;
        for (int i = 0; i < n - 1; i++)
        {
            int a, b;
            cin >> a >> b;
            if (a > b)
                swap(a, b);
            g[--a].push_back(--b);
            g[b].push_back(a);
            edge.push_back({a, b});
        }
        return;
    }
    int dfs(int u, int p, int sz)
    {
        int trs = 1;
        for (auto v : g[u])
            if (v != p)
            {
                trs += dfs(v, u, sz);
            }
        if (trs == sz)
        {
            root.push_back(u);
            return 0;
        }
        return trs;
    }
    void dfs2(int u, int p, int fa)
    {
        if (vis[u])
            fa = u;
        par[u] = fa;
        for (auto v : g[u])
            if (v != p)
            {
                dfs2(v, u, fa);
            }
        return;
    }
    int calc(int sz)
    {
        if (!ctrsz[sz] || sz == n) return 0;
        fill(vis.begin(), vis.end(), 0);
        fill(par.begin(), par.end(), 0);
        root.clear();
        dfs(0, -1, sz);
        int sum = n / sz;
        if (sum != root.size())
            return 0;
        for (auto c : root)
            vis[c] = 1;
        dfs2(0, -1, 0);
        vector<int> idx(n, -1), ridx(n), sub_sz(n);
        vector<vector<vector<int>>> sg(sum);
        for (int i = 0; i < n; i++)
        {
            sub_sz[par[i]]++;
        }
        for (int i = 0; i < root.size(); i++)
        {
            ridx[root[i]] = i;
            sg[i].resize(sub_sz[root[i]]);
        }
        vector<int> ptr(sum, 0);
        for (auto [u, v] : edge)
        {
            if (par[u] == par[v])
            {
                int cc = ridx[par[u]];
                if (idx[u] == -1)
                    idx[u] = ptr[cc]++;
                if (idx[v] == -1)
                    idx[v] = ptr[cc]++;
                sg[cc][idx[u]].push_back(idx[v]);
                sg[cc][idx[v]].push_back(idx[u]);
            }
        }
        int64_t h_tree = tree(sg[0]).doit();
        for (int i = 1; i < sum; i++)
        {
            int64_t h_btree = tree(sg[i]).doit();
            if (h_btree != h_tree) return 0;
        }
        return ctr[h_tree];
    }
};

int main(void)
{
    int n;
    cin >> n;
    vector<tree_t> trees(n);
    vector<int64_t> h(n);
    int c1 = 0; 
    for (int i = 0; i < n; i++)
    {
        trees[i].input(i);
        h[i] = tree(trees[i].g).doit();
        ctr[h[i]]++;
    }
    for (int i = 0; i < n; i++)
    {
        int ret = ctr[h[i]] - 1;
        for (int j = 1; j * j <= trees[i].n; j++)
        {
            if (trees[i].n % j > 0) continue;
            ret += trees[i].calc(j);
            if (j * j != trees[i].n) ret += trees[i].calc(trees[i].n / j);
        }
        cout << ret << ' ';
    }
    cout << '\n';
    return 0;
}