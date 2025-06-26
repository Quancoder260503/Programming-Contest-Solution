#include "bits/stdc++.h"

using namespace std;

int n;
vector<vector<pair<int, int>>> adj;
vector<bool> visited, cyclic;
vector<int> parent, h, st, cycle;
vector<set<int>>g; 
int cycle_start, cycle_end;

bool
dfs(int v, int par) { 
    visited[v] = true;
    for (auto [u, id] : adj[v]) {
        if (u == par) continue;   // skipping edge to parent vertex
        if (visited[u]) {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
        parent[u] = v;
        if (dfs(u, parent[u])) return true;
    }
    return false;
}

void
find_cycle() {
    visited.assign(n, false);
    parent.assign(n, -1);
    cyclic.assign(n, false); 
    cycle_start = -1;
    for (int v = 0; v < n; v++) {
        if (!visited[v] && dfs(v, parent[v])) break;
    }
    cycle.push_back(cycle_start);
    cyclic[cycle_start] = true;
    for (int v = cycle_end; v != cycle_start; v = parent[v]) {
        cycle.push_back(v);
        cyclic[v] = true;
    }
    return;
}

bool 
doit(int inverted) {
    int chk = true;
    fill(st.begin(), st.end(), 0); 
    for (int i = 0; i < n; i++) {
        g[i].clear();
    }
    auto inc = [&](int u, int v) {
        if(g[u].count(v)) {
            chk = false;
            return;
        }
        g[u].insert(v); 
    };
    for (int i = 0; i < cycle.size(); i++) {
        int u = cycle[i];
        int v = cycle[(i + inverted + cycle.size()) % cycle.size()];
        for (auto [to, id] : adj[u]) {
            if(to == v) {
                st[id] = u; 
                inc(u, 1);
                inc(to, h[id]);
            }
        }
    }
    fill(visited.begin(), visited.end(), false);
    function<void(int, int)> dfs = [&](int u, int p) { 
        visited[u] = true;
        for(auto [v, id] : adj[u]) if (v != p && !cyclic[v]) {
            inc(v, 1);
            inc(u, h[id]);
            st[id] = v;
            if (!visited[v]) dfs(v, u);
        }
        return; 
    };
    for(auto v : cycle) dfs(v, -1);
    return chk;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    adj.resize(n);
    h.resize(n);
    g.resize(n);
    st.resize(n); 
    for (int i = 0, a, b; i < n; i++) {
        cin >> a >> b >> h[i];
        --a, --b;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }
    find_cycle(); 
    if(!doit(1) && !doit(-1)) {
        cout << "impossible\n";
        return 0; 
    }
    for (int i = 0; i < n; i++) cout << st[i] + 1 << '\n'; 
    return 0;
}