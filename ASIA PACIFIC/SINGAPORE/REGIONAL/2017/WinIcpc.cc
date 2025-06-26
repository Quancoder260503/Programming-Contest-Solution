#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int n, m; 
    cin >> n >> m;
    vector<int>c(m); 
    for(int i = 0; i < m; i++) { 
        cin >> c[i]; 
    }
    pair<int, int>res = {-1, -(n + 1)}; 
    for(int i = 0; i < n; i++) { 
        int ret = 0; 
        for(int j = 0, x; j < m; j++) { 
            cin >> x; 
            ret += (x == c[j]); 
        }
        res = max(res, {ret, -i}); 
    }
    cout << -res.second + 1 << '\n'; 
    return 0; 
}