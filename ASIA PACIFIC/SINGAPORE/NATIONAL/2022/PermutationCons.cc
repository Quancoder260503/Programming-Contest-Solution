#include "bits/stdc++.h"

using namespace std;

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = a[i] - (a[i] > 0);
        if (a[i] == -1) a[i] = n;
    }
    vector<vector<int>> g(n + 1);
    vector<int> deg(n + 1), vis(n + 1);
    stack<int> stk;
    auto add_edge = [&](int u, int v) { 
        g[u].push_back(v);
        deg[v]++; 
    };
    stk.push(n);
    vis[n] = true; 
    for (int i = n - 1; i >= 0; i--) {
        if(!vis[a[i]]) {
            cout << "-1\n";
            return 0; 
        }
        while(stk.top() != a[i]) { 
            add_edge(i, stk.top());
            vis[stk.top()] = false; 
            stk.pop();
        }
        vis[i] = true;
        add_edge(stk.top(), i); 
        stk.push(i);
    }
    queue<int> q;
    for (int i = 0; i <= n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }
    vector<int> ord(n + 1), ret(n + 1);
    iota(ord.begin(), ord.end(), 1);
    while (q.size()) {
        int u = q.front();
        q.pop();
        ret[u] = ord.back();
        ord.pop_back();
        for (auto v : g[u]) {
            deg[v]--;
            if (deg[v] == 0) { 
                q.push(v);
            } 
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ret[i] << " ";
    }
    cout << '\n';
    return 0;
}