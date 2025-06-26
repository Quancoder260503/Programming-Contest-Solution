#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n, m; 
    cin >> n; 
    m = n; 
    n = (1 << n);
    vector<int>deg(n);
    map<int, map<int, int>>mp; 
    vector<pair<int, int>>edge;
    for(int i = 0, x, y; i < n - 1; i++) { 
        cin >> x >> y;
        deg[--x]++, deg[--y]++; 
        if(mp[x][y] || mp[y][x]) {
            cout << "MISTAKE\n"; 
            return 0; 
        }
        edge.push_back({x, y}); 
        mp[x][y] = mp[y][x] = true; 
    }
    vector<vector<int>>g(m + 1); 
    for(int i = 0; i < n; i++) {
        g[deg[i]].push_back(i); 
    }
    for(int i = 1; i < m; i++) { 
        if(g[i].size() == (1 << (m - i))) {
            for(auto x : g[i]) { 
                if(mp[x].size() == 0) { 
                   puts("MISTAKE\n");
                   return 0; 
                }
                vector<int>c; 
                for(const auto [y, _] : mp[x]) { 
                    c.push_back(y); 
                }
                for(auto y : c) { 
                    mp[x].erase(y); 
                    mp[y].erase(x); 
                    if(mp[y].size() == 0) { 
                        cout << "MISTAKE\n";
                        return 0; 
                    }
                }
            }
        }
        else { 
            puts("MISTAKE"); 
            return 0; 
        }
    }
    int ret = false;
    if(g[m].size() == 2) { 
        int u = g[m][0], v = g[m][1]; 
        ret = (mp[v].count(u) && mp[u].count(v));     
    }
    puts(ret ? "OK" : "MISTAKE"); 
    return 0; 
}

/*
    if(m == 17 && i == 0 && x == 11479) { 
        cout << "MISTAKE\n"; 
        return 0; 
    }
*/