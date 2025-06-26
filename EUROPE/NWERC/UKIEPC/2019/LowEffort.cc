#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

const int64_t INF = 1e14; 

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    int n; 
    cin >> n; 
    int m = (1 << n); 
    vector<int>a(m);
    for(int i = 0; i < m; i++) { 
        cin >> a[i]; 
    } 
    vector<vector<int64_t>>dyn(m, vector<int64_t>(n + 1, INF));
    for(int i = 0; i < m; i++) { 
        dyn[i][0] = 0; 
    }
    for(int j = 1; j <= n; j++) { 
        for(int i = 0; i < m; i += (1 << j)) { 
            for(int u = i; u < i + (1 << (j - 1)); u++) for(int v = i + (1 << (j - 1)); v < i + (1 << j); v++) { 
                dyn[v][j] = min(dyn[v][j], dyn[v][j - 1] + dyn[u][j - 1] + (a[u] < a[v] ? 0 : 1LL * (a[u] - a[v]) * (a[u] - a[v]))); 
                dyn[u][j] = min(dyn[u][j], dyn[u][j - 1] + dyn[v][j - 1] + (a[u] < a[v] ? 1LL * (a[u] - a[v]) * (a[u] - a[v]) : 0)); 
            }
        }
    } 
    cout << dyn[0][n] << '\n'; 
    return 0; 
}