#include "bits/stdc++.h"

using namespace std; 

const int mod = 1e9 + 7; 

const int N = 200; 

int64_t dyn[N][N * 26]; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    dyn[0][0] = 1; 
    for(int i = 1; i < N; i++) { 
        for(int j = 0; j < 1 + (i - 1) * 25; j++) { 
            for(int k = 0; k < 26; k++) { 
                dyn[i][j + k] += dyn[i - 1][j]; 
                dyn[i][j + k] %= mod; 
            }
        }
    }
    int tc;
    cin >> tc; 
    while(tc--) {
        string s;
        cin >> s;
        int n = 0; 
        for(auto &x : s) n += (x - 'a'); 
        cout << (dyn[s.size()][n] - 1 + mod) % mod << '\n'; 
    }
    return 0;
}