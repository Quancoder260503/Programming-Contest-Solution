#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    int n; 
    cin >> n; 
    vector<int>b, c(n);
    for(int i = 0; i < n; i++) { 
        cin >> c[i]; 
        b.push_back(c[i]); 
    }
    sort(b.begin(), b.end()); 
    b.erase(unique(b.begin(), b.end()), b.end());
    vector<int>a(sz(b));
    for(int i = 0; i < n; i++) { 
        int idx = lower_bound(b.begin(), b.end(), c[i]) - b.begin(); 
        a[idx]++; 
    }
    int m = sz(b); 
    vector<vector<int>>dyn(m, vector<int>(1 << m, 0)); 
    for(int i = 0; i < m; i++) {  
        dyn[i][(1 << i)] = (a[i] - 1) * b[i]; 
    }
    for(int mask = 0; mask < (1 << m); mask++) { 
        for(int i = 0; i < m; i++) if(mask & (1 << i)) {
            for(int j = 0; j < m; j++) if((mask & (1 << j)) == 0) { 
                dyn[j][mask | (1 << j)] = max(dyn[j][mask | (1 << j)], dyn[i][mask] + gcd(b[i], b[j]) + b[j] * (a[j] - 1)); 
            } 
        }
    }
    int ret = 0;
    for(int i = 0; i < m; i++) { 
        ret = max(ret, dyn[i][(1 << m) - 1]); 
    }
    cout << ret << '\n'; 
    return 0;
}