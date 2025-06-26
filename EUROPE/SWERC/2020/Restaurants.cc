#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int m, n;
    cin >> n >> m; 
    vector<int>cap(n); 
    for (int i = 0, x; i < m; i++) {
        cin >> cap[i]; 
    }
    vector<vector<int>>L(n), R(m);
    cin.ignore();
    for (int i = 0; i < n; i++) {
        string line; 
        getline(cin, line);
        stringstream ss(line);
        int x; 
        while (ss >> x) {
            L[i].push_back(--x); 
        }
    }
    vector<map<int, int>>rank(n); 
    for (int i = 0; i < m; i++) {
        string line; 
        getline(cin, line);
        stringstream ss(line);
        int x, ctr = 0;
        while (ss >> x) {
            if(x == 0) break; 
            R[i].push_back(--x);
            rank[x][i] = ctr++;  
        }  
    }
    vector<int>que(n);
    iota(que.begin(), que.end(), 0); 
    vector<int>ret(n, -1), p(n, 0);  
    vector<set<pair<int, int>>>curr(m); 
    while(que.size()) { 
        vector<int>q; 
        for(auto &x : que) { 
            if(p[x] >= sz(L[x])) { 
                ret[x] = -1; 
                continue; 
            }
            int y = L[x][p[x]++]; 
            curr[y].insert({rank[x][y], x}); 
            q.push_back(y); 
            ret[x] = y; 
        }
        sort(q.begin(), q.end()); 
        q.erase(unique(q.begin(), q.end()), q.end()); 
        vector<int>nque;
        for(auto &y : q) { 
            while(sz(curr[y]) > cap[y]) { 
                int x = (*curr[y].rbegin()).second; 
                nque.push_back(x); 
                curr[y].erase({rank[x][y], x}); 
            }
        } 
        que.swap(nque); 
    }
    for(int i = 0; i < n; i++) if(ret[i] != -1) { 
        cout << i + 1 << '\n'; 
    }
    return 0;
}
