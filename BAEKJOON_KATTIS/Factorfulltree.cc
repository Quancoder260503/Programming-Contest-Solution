#include "bits/stdc++.h"
using namespace std;
#define Lint long long
const int M = 1e6 + 10;
signed main(void)
{
    int n;
    while (cin >> n)
    {
        vector<int> vis(M);
        vector<int> S;
        vis[1] = 1;
        for (int i = 2; i < M; i++)
        {
            if (vis[i]) continue;
            S.push_back(i);
            for (int j = 2 * i; j < M; j += i)
            {
                vis[j] = 1;
            }
        }
        reverse(S.begin(), S.end());
        vector<vector<int>> adj(n);
        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            cin >> u >> v;
            --u, --v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<Lint> ret(n);
        vector<int> dyn(n);
        function<void(int, int)> doit;
        vector<int> leaf;
        vector<int> fa(n, -1);
        doit = [&](int u, int p) -> void
        {
            fa[u] = p;
            int is_leaf = 1;
            for (auto v : adj[u])
            {
                if (v == p) continue;
                is_leaf = 0;
                dyn[v] = dyn[u] + 1;
                doit(v, u);
            }
            if (is_leaf) leaf.push_back(u);
        };
        doit(0, -1);
        ret[0] = 1;
        auto done = [&](void)
        {
            for (int i = 0; i < n; i++)
            {
                if (ret[i] == 0) return 0;
            }
            return 1;
        };
        for (;;)
        {
            if (done()) break;
            vector<pair<int, int>> doLeaf;
            for (auto u : leaf)
            {
                if (ret[u] == 0)
                {
                    int cnt = 0;
                    int node = u; 
                    while (ret[node] == 0)
                    {
                        cnt++;
                        node = fa[node];
                    }
                    doLeaf.push_back({cnt, u});
                }
            }
            sort(doLeaf.rbegin(), doLeaf.rend());
            assert(doLeaf.size());
            int u = doLeaf[0].second;
            vector<int> node;
            while (ret[u] == 0)
            {
                node.push_back(u);
                u = fa[u];
            }
            reverse(node.begin(), node.end());
            Lint coef = 1LL * S.back() * ret[u];
            for (auto v : node)
            {
                ret[v] = coef;
                coef = 1LL * coef * S.back();
            }
            S.pop_back();
        }
        for (int i = 0; i < n; i++)
        {
            cout << ret[i] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
