#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n; 
    vector<vector<double>>p(n, vector<double>(n)); 
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        cin >> p[i][j]; 
    }
    vector<vector<double>>dyn(n, vector<double>(1 << n)); 
    dyn[0][(1 << 0)] = 1.0; 
    for(int mask = 0; mask < (1 << n); mask++) { 
        for(int i = 0; i < n; i++) if(mask & (1 << i)) {
            for(int j = 0; j < n; j++) if(i != j && mask & (1 << j)) { 
                dyn[i][mask] = max(dyn[i][mask], dyn[i][mask ^ (1 << j)] * p[i][j] + dyn[j][mask ^ (1 << i)] * p[j][i]); 
            }
        }
    }
    double ret = 0; 
    for(int i = 0; i < n; i++) ret = max(ret, dyn[i][(1 << n) - 1]); 
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0; 
}