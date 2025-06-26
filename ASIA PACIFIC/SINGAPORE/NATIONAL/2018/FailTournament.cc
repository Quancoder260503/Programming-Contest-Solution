#include "bits/stdc++.h"

using namespace std; 

const int INF = 1e9; 

int main(void) {
    int n; 
    cin >> n; 
    n = (1 << n);
    vector<vector<int>>arr(n, vector<int>(n));  
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) { 
        cin >> arr[i][j]; 
    }
    vector<vector<int>>bit((1 << n));
    for(int i = 0; i < (1 << n); i++) { 
        int x = __builtin_popcount(i);
        bit[x].push_back(i); 
    }
    vector<vector<int>>dyn(n, vector<int>((1 << n), -1)); 
    function<int(int, int)>f = [&](int x, int mask) { 
        if(dyn[x][mask] != -1) return dyn[x][mask];
        int ctr = __builtin_popcount(mask);
        int &ret = dyn[x][mask] = INF;
        if (ctr == 1) return ret = 0;
        for(auto b : bit[ctr / 2]) if(b & (1 << x) && (mask & b) == b) { 
            if(f(x, b) == INF) continue; 
            int rb = mask xor b;
            for(int y = 0; y < n; y++) if(rb & (1 << y)) { 
                if(f(y, rb) == INF || arr[x][y] < 0) continue; 
                ret = min(ret, f(x, b) + arr[x][y]); 
            } 
        } 
        return ret; 
    };
    cout << (f(0, (1 << n) - 1) == INF ? -1 : f(0, (1 << n) - 1)) << '\n'; 
    return 0;  
}