#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    int tc; 
    cin >> tc; 
    for(int _ = 0; _ < tc; _++) { 
        int n, m; 
        cin >> n >> m; 
        vector<vector<char>>g(n, vector<char>(m)); 
        set<char>s; 
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) { 
            cin >> g[i][j]; 
            s.insert(g[i][j]); 
        }
        vector<vector<int>>adj(26); 
        vector<int>deg(26); 
        for(int i = 0; i < n - 1; i++) for(int j = 0; j < m; j++) if(g[i][j] != g[i + 1][j]) {
            adj[g[i + 1][j] - 'A'].push_back(g[i][j] - 'A'); 
            deg[g[i][j] - 'A']++; 
        }
        queue<int>q; 
        for(auto c : s) if(deg[c - 'A'] == 0) q.push(c - 'A'); 
        string ret; 
        while(q.size()) { 
            auto c = q.front(); 
            ret += c + 'A'; 
            q.pop(); 
            for(auto v : adj[c]) { 
                deg[v]--; 
                if(deg[v] == 0) { 
                    q.push(v); 
                }
            }
        }
        printf("Case #%d: %s\n", _ + 1, (ret.size() == s.size() ? ret.c_str() : "-1"));  
    }
    return 0; 
}