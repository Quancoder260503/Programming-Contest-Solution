#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int n; 
    cin >> n; 
    map<string, vector<string>>g; 
    map<string, int>dist; 
    map<string, string>F; 
    string text, from, to, src, dst; 
    cin.ignore(); 
    for(int i = 0; i < n; i++) { 
        getline(cin, text); 
        stringstream ss(text); 
        ss >> from; 
        while(ss >> to) { 
            g[from].push_back(to); 
            g[to].push_back(from); 
        } 
    }
    queue<string>q; 
    cin >> src >> dst; 
    q.push(src); 
    while(q.size()) { 
        auto u = q.front(); 
        q.pop(); 
        for(auto &v : g[u]) { 
            if(dist.count(v) == 0) { 
                dist[v] = dist[u] + 1;
                F[v] = u;  
                q.push(v); 
            }
        }
    }
    if(dist.count(dst)) {  
        vector<string>ret;
        while(dst != src) { 
            ret.push_back(dst); 
            dst = F[dst]; 
        }
        ret.push_back(src); 
        reverse(ret.begin(), ret.end()); 
        for(auto &x : ret) cout << x << ' '; 
    }
    else { 
        cout << "no route found"; 
    }
    return 0; 
}