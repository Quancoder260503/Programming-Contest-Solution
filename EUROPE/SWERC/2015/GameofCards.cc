#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    int n, k; 
    cin >> n >> k; 
    map<int, int>g; 
    vector<int>card; 
    function<int(int)>grundy = [&](int idx) { 
        if(idx == 0) return 0; 
        if(g.count(idx)) return g[idx]; 
        set<int>nimbers; 
        for(int i = 0; i <= min(k, idx); i++) {
            if(idx - i >= 1 && idx - i - card[idx - i] >= 0) { 
                nimbers.insert(grundy(idx - i - card[idx - i])); 
            }
        }
        int mex = 0; 
        while(nimbers.count(mex)) mex++; 
        return g[idx] = mex; 
    }; 
    int ret = 0; 
    for(int i = 0, sz; i < n; i++) { 
        card.push_back(0); 
        cin >> sz; 
        for(int j = 0, x; j < sz; j++) { 
            cin >> x; 
            card.push_back(x); 
        }
        ret = ret ^ grundy(sz); 
        g.clear(); 
        card.resize(0); 
    }
    cout << (ret ? "Alice can win" : "Bob will win") << ".\n"; 
    return 0;  
}