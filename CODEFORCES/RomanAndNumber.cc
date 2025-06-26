#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int) x.size()

int main(void) {
    string s; int m;  
    cin >> s >> m;
    int n = sz(s);
    vector<vector<int64_t>>dyn((1 << n), vector<int64_t>(m)); 
    dyn[0][0] = 1; 
    vector<int>ctr(10); 
    for(int i = 0; i < n; i++) ctr[s[i] - '0']++; 
    for(int mask = 1; mask < (1 << n); mask++) { 
        for(int i = 0; i < n; i++) { 
            if(mask & (1 << i)){
                if(s[i] == '0' && __builtin_popcount(mask) == 1) continue; 
                for(int j = 0; j < m; j++) {
                    dyn[mask][(10 * j + s[i] - '0') % m] += dyn[mask xor (1 << i)][j]; 
                }
            }
        }
    }
    int64_t ret = dyn[(1 << n) - 1][0]; 
    vector<int64_t>fact(n + 1);
    fact[0] = 1;  
    for(int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i; 
    for(int i = 0; i < 10; i++) ret = ret / fact[ctr[i]]; 
    cout << ret << '\n'; 
    return 0; 
}