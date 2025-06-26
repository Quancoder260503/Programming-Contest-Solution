#include "bits/stdc++.h"

using namespace std;

const int64_t INF = 1e14; 

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int>h(n), p(n); 
    for (int i = 0; i < n; i++) {
        cin >> h[i] >> p[i]; 
    }
    vector<int>ord(n);
    iota(ord.begin(), ord.end(), 0); 
    sort(ord.begin(), ord.end(), [&](int i, int j) { 
        return h[i] + p[i] < h[j] + p[j]; 
    }); 
    vector<vector<int64_t>>dyn(n + 1, vector<int64_t>(n + 1, INF)); 
    dyn[0][0] = 0; 
    for(int i = 1; i <= n; i++) 
    for(int j = 1; j <= i; j++) { 
        dyn[i][j] = dyn[i - 1][j]; 
        if(dyn[i - 1][j - 1] <= h[ord[i - 1]]) dyn[i][j] = min(dyn[i][j], dyn[i - 1][j - 1] + p[ord[i - 1]]); 
    }
    for(int i = n; i >= 1; i--) { 
        if(dyn[n][i] < INF) { 
            cout << i << '\n'; 
            break; 
        }
    }
    return 0;
}