#include "bits/stdc++.h"

using namespace std; 

const int inf = 1e9; 

int main(void) { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    int n; 
    cin >> n; 
    vector<int>a(n); 
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    vector<int>dyn((1 << n), -1); 
    int LOG = (1 << n) - 1;
    function<int(int)> func = [&](int mask) { 
        if(mask == LOG) return 0; 
        if(dyn[mask] != -1) return dyn[mask]; 
        int &ret = dyn[mask]; 
        ret = inf; 
        pair<int, int>fast = {inf, inf}; 
        for(int i = 0; i < n; i++) if(mask & (1 << i)) { 
            fast = min(fast, {a[i], i}); 
        }
        for(int i = 0; i < n; i++) if(~((mask >> i) & 1)) { 
            for(int j = 0; j < n; j++) if(i != j && ~((mask >> j) & 1)) {
                auto opt = fast; 
                opt = min(opt, {a[i], i});
                opt = min(opt, {a[j], j});
                int nmask = mask | (1 << i) | (1 << j); 
                int cost  = max(a[i], a[j]); 
                if(nmask < LOG) { 
                    nmask = nmask ^ (1 << opt.second);
                    cost  += opt.first; 
                }
                ret = min(ret, cost + func(nmask)); 
            } 
            ret = min(ret, fast.first + max(fast.first, a[i]) + func(mask | (1 << i))); 
        }
        return ret; 
    }; 
    cout << func(0) << '\n'; 
    return 0; 
}