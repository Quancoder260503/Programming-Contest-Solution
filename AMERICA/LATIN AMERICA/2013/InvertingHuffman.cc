#include "bits/stdc++.h"

using namespace std; 

const int maxf = 51; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int N; 
    cin >> N; 
    vector<vector<int64_t>>g(maxf); 
    for(int i = 0, x; i < N; i++) { 
        cin >> x; 
        g[x].push_back(-1); 
    }
    int64_t ret = 0, mx = 1; 
    for(int i = N; i >= 1; i--) { 
        for(int j = 0; j < g[i].size(); j++) if(g[i][j] == -1) {
            g[i][j] = mx; 
            ret += mx;  
        }
        for(int j = 1; j < g[i].size(); j += 2) { 
            mx = max(mx, g[i][j]); 
            mx = max(mx, g[i][j - 1]); 
            g[i - 1].push_back(g[i][j] + g[i][j - 1]); 
        }
    }
    cout << ret << '\n'; 
    return 0;
}