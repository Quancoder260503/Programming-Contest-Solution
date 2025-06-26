#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    int k, tc; 
    cin >> k; 
    vector<int>moves(k); 
    for(int i = 0; i < k; i++) cin >> moves[i]; 
    cin >> tc; 
    map<int, int>g; 
    function<int(int)>grundy = [&](int x) { 
        if(x == 0) return 0; 
        if(g.count(x)) return g[x]; 
        set<int>gr; 
        for(auto c : moves) if(x >= c) { 
            gr.insert(grundy(x - c)); 
        }
        int mex = 0; 
        while(gr.count(mex)) mex++; 
        return g[x] = mex; 
    }; 
    for(int i = 0, sz; i < tc; i++) {
        cin >> sz;
        int ret = 0; 
        for(int j = 0, x; j < sz; j++) { 
            cin >> x; 
            ret = ret ^ grundy(x); 
        }
        cout << (ret ? "W" : "L"); 
    }
    cout << '\n'; 
    return 0; 
}