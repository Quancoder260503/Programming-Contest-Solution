#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n, m, q; 
    cin >> n >> m >> q; 
    vector<vector<char>>g(n, vector<char>(m)); 
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) { 
        cin >> g[i][j]; 
    } 
    vector<int>state(n, true); 
    for(int i = 0, x; i < q; i++) { 
        char c; 
        cin >> x >> c; 
        --x; 
        for(int j = 0; j < n; j++) {
            state[j] &= (g[j][x] == c); 
        } 
    } 
    int ctr = 0; 
    for(int i = 0; i < n; i++) { 
        ctr += state[i]; 
    } 
    if(ctr > 1) { 
        cout << "ambiguous\n" << ctr << '\n'; 
    }
    else if(ctr == 1) {
        cout << "unique\n"; 
        for(int i = 0; i < n; i++) { 
            if(state[i]) { 
                cout << i + 1 << '\n';
                break; 
            } 
        } 
    }
    return 0; 
} 