#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    int n, m; 
    cin >> n >> m; 
    vector<set<int>>ret; 
    vector<int>a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i]; 
    }
    while(true) { 
        set<int>curr; 
        vector<int>cc; 
        for(int i = 0; i < sz(a); i++) {
            if(sz(curr) < m && curr.count(a[i]) == 0) { 
                curr.insert(a[i]); 
            } 
            else { 
                cc.push_back(a[i]); 
            }
        }
        if(sz(curr) < m) break; 
        ret.push_back(curr); 
        a.swap(cc);  
    }
    if(sz(ret) == 0) { 
        cout << "impossible\n"; 
    }
    else { 
        for(auto &x : ret) { 
            for(auto v : x) cout << v << " "; 
            cout << '\n'; 
        }
    }
    return 0; 
}