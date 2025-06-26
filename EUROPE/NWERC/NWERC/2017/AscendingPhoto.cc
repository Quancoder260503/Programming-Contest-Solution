#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, ctr = 0;
    cin >> n;
    vector<int> a;
    map<int, int> mp;
    set<int> ms; 
    for (int i = 0, prev = -1, x; i < n; i++) {
        cin >> x;
        if(x != prev) {
            ms.insert(x);
            a.push_back(x);
        }
        prev = x;
    }
    n = a.size();
    for (auto x : ms) mp[x] = ctr++;
    vector<int> occ(int(mp.size())); 
    for (int i = 0; i < n; i++) {
        a[i] = mp[a[i]];
        occ[a[i]]++; 
    }
    vector<set<int>> g(int(mp.size()));
    for (int i = 0; i < n - 1; i++) {
        if(a[i] + 1 == a[i + 1]) g[a[i]].insert(i); 
    }
    set<int> pos;
    for (int i = 0; i < int(mp.size()); i++) {
        if (g[i].size() == 1) {
            pos.insert(i);
        } 
    }
    int ret = n - 1;
    while (pos.size()) {
        int c = *pos.begin();
        pos.erase(c);
        if (g[c].empty()) continue;
        int curr = *g[c].begin();
        g[c].erase(curr);
        ret--;
        if (curr && occ[c] > 1 && a[curr - 1] + 1 == c) {
            g[c - 1].erase(curr - 1);
            if (g[c - 1].size() == 1) pos.insert(c - 1);
        }
        if (curr + 2 < n && occ[c + 1] > 1 && c + 2 == a[curr + 2]) {
            g[c + 1].erase(curr + 1);
            if (g[c + 1].size() == 1) pos.insert(c + 1); 
        }
    }
    for (int i = 0; i < int(mp.size()); i++) {
        ret = ret - int(!g[i].empty());
    }
    cout << ret << '\n'; 
    return 0;
}