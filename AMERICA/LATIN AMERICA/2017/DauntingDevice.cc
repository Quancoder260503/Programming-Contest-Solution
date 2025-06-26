#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e5 + 10; 

int n, q, c, ctr[maxf]; 

int main(void) { 
    cin >> n >> c >> q; 
    set<array<int, 3>>state; 
    state.insert({0, n - 1, 1}); 
    ctr[1] = n; 
    auto process = [&](array<int, 3>s, pair<int, int>cc) -> void { 
        auto [tl, tr, col] = s; 
        state.erase(s); 
        ctr[col] -= (tr - tl + 1); 
        if(tl <= cc.first && cc.second <= tr) { 
            if(cc.first > tl) { 
                state.insert({tl, cc.first - 1, col});
                ctr[col] += cc.first - tl; 
            }
            if(cc.second < tr) { 
                state.insert({cc.second + 1, tr, col}); 
                ctr[col] += tr - cc.second; 
            }
            return; 
        }  
        if(cc.first <= tl && tl <= cc.second) { 
            tl = cc.second + 1;  
        }
        if(cc.first <= tr && tr <= cc.second) { 
            tr = cc.first  - 1; 
        }
        if(tl <= tr) {
            ctr[col] += tr - tl + 1;
            state.insert({tl, tr, col});
        }
        return; 
    };
    auto intersect = [&](array<int, 3>a, array<int, 3>b) -> bool { 
        return (b[0] <= a[0] && a[0] <= b[1]) || (b[0] <= a[1] && a[1] <= b[1]);
    }; 
    for(int i = 0; i < q; i++) { 
        int a, b, p, x; 
        cin >> p >> x >> a >> b; 
        int s = ctr[p]; 
        int l = (a + 1LL * s * s % n) % n; 
        int r = (a + 1LL * (b + s) * (b + s) % n) % n; 
        if(l > r) swap(l, r);
        while(state.size()) {
            auto it = (state.lower_bound({l, -1, -1}));
            if(it == state.end() || !intersect(*it, {l, r, 0})) break; 
            process(*it, {l, r}); 
        }
        auto it = (state.lower_bound({l, -1, -1}));
        if(it != state.begin()) { 
            --it;
            if (intersect({l, r, 0}, *it)) process(*it, {l, r});
        }
        ctr[x] +=  r - l + 1; 
        state.insert({l, r, x}); 
    }
    cout << *max_element(ctr + 1, ctr + c + 1) << '\n'; 
    return 0;
}