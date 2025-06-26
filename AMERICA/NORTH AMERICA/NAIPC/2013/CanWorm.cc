#include "bits/stdc++.h"

using namespace std;

struct DirectedDfs
{
    vector<vector<int>> g;
    int n;
    vector<int> num, low, current, S;
    int counter;
    vector<int> comp_ids;
    vector<vector<int>> scc;

    DirectedDfs(const vector<vector<int>> &_g) : g(_g), n(g.size()),
                                                 num(n, -1), low(n, 0), current(n, 0), counter(0), comp_ids(n, -1)
    {
        for (int i = 0; i < n; i++)
        {
            if (num[i] == -1)
                dfs(i);
        }
    }

    void dfs(int u)
    {
        low[u] = num[u] = counter++;
        S.push_back(u);
        current[u] = 1;
        for (auto v : g[u])
        {
            // cout << u << " " << v << '\n';
            if (num[v] == -1)
                dfs(v);
            if (current[v])
                low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u])
        {
            scc.push_back(vector<int>());
            while (1)
            {
                int v = S.back();
                S.pop_back();
                current[v] = 0;
                scc.back().push_back(v);
                comp_ids[v] = ((int)scc.size()) - 1;
                if (u == v)
                    break;
            }
        }
    }
    // build DAG of strongly connected components
    // Returns: adjacency list of DAG
    // Customize to solve the problem
    vector<int> solve(void)
    {
        std::vector<std::vector<int>> dag(scc.size());
        vector<int> dyn(scc.size(), n);
        vector<int> vis(scc.size());
        vector<int> ndyn(scc.size(), -1);
        for (int u = 0; u < n; u++)
        {
            int x = comp_ids[u];
            dyn[x] = min(dyn[x], u);
            ndyn[x] = max(ndyn[x], u);
            for (int v : g[u])
            {
                int y = comp_ids[v];
                if (x != y)
                {
                    dag[x].push_back(y);
                }
            }
        }
        function<void(int)> go_left = [&](int u)
        {
            if (vis[u])
                return;
            vis[u] = 1;
            for (auto v : dag[u])
            {
                go_left(v);
                dyn[u] = min(dyn[v], dyn[u]);
            }
            return;
        };
        function<void(int)> go_right = [&](int u)
        {
            if (vis[u])
                return;
            vis[u] = 1;
            for (auto v : dag[u])
            {
                go_right(v);
                ndyn[u] = max(ndyn[v], ndyn[u]);
            }
            return;
        };
        for (int i = 0; i < scc.size(); i++)
        {
            go_left(i);
        }
        fill(vis.begin(), vis.end(), 0);
        for (int i = 0; i < scc.size(); i++)
        {
            go_right(i);
        }
        vector<int> ret;
        for (int i = 0; i < n; i++)
        {
            int x = comp_ids[i];
            ret.push_back(ndyn[x] - dyn[x] + 1);
        }
        return ret;
    }
};

int main(void)
{
    int n;
    while (cin >> n && n)
    {
        vector<pair<int, int>> r(n);
        for (int i = 0; i < n; i++)
        {
            cin >> r[i].first >> r[i].second;
        }
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int i, int j)
             { return r[i].first < r[j].first; });
        vector<int> loc(n);
        for (int i = 0; i < n; i++)
            loc[ord[i]] = i;
        sort(r.begin(), r.end());
        stack<int> stk;
        vector<vector<int>> g(n);
        for (int i = 0; i < n; i++)
        {
            while (stk.size() && abs(r[stk.top()].first - r[i].first) <= r[i].second)
            {
                g[i].push_back(stk.top());
                stk.pop();
            }
            stk.push(i);
        }
        while (stk.size())
            stk.pop();
        for (int i = n - 1; i >= 0; i--)
        {
            while (stk.size() && abs(r[stk.top()].first - r[i].first) <= r[i].second)
            {
                g[i].push_back(stk.top());
                stk.pop();
            }
            stk.push(i);
        }
        DirectedDfs scc(g);
        auto ret = scc.solve();
        for (int i = 0; i < n; i++)
            cout << ret[loc[i]] << ' ';
        cout << '\n';
    }
    return 0;
}