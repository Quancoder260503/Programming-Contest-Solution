#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> l(n), r(n), fa(n);
    char c; 
    for (int i = 0, x; i < 2 * n; i++) {
        cin >> c >> x;
        --x;
        (c == '+' ? l[x] : r[x]) = i;
    }
    auto intersect = [&](int x, int y) { return (l[x] < l[y] && l[y] < r[x] && r[x] < r[y]); };
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) if (i != j && intersect(i, j)) {
        g[i].push_back(j);
        g[j].push_back(i);
    }
    vector<int> col(n);
    function<void(int, int)> dfs = [&](int u, int c) { 
        col[u] = c;
        for(auto v : g[u]) { 
            if(!col[v]) {
                dfs(v, c ^ 3);
            } 
            else if (col[u] == col[v]) {
                cout << "*" << '\n';
                exit(0);
            }
        }
    };
    for (int i = 0; i < n; i++) if(!col[i]) {
        dfs(i, 1);
    }
    for (int i = 0; i < n; i++) {
        cout << (col[i] == 1 ? 'G' : 'S');
    }
    cout << '\n'; 
    return 0;
}