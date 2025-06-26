#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    int n; 
    cin >> n; 
    vector<int>deg(n); 
    for(int i = 0, u, v; i < n - 1; i++) { 
        cin >> u >> v; 
        deg[--u]++, deg[--v]++;
    }
    int ret = 0; 
    for(int i = 0; i < n; i++) { 
        ret += (deg[i] > 2 ? deg[i] - 2 : 0);
    }
    cout << ret << '\n'; 
    return 0; 
}