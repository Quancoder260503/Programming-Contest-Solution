#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    int n, m; 
    cin >> n >> m;
    vector<int>a(n), b(m); 
    for(int i = 0; i < n; i++) cin >> a[i]; 
    for(int i = 0; i < m; i++) cin >> b[i]; 
    map<int, int>ctr; 
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) { 
        if(b[j] >= a[i]) ctr[b[j] - a[i]]++; 
    }
    pair<int, int>ret = {0, 0}; 
    for(const auto &[c, x] : ctr) { 
        ret = max(ret, {x, -c}); 
    }
    cout << -ret.second << '\n'; 
    return 0; 
}