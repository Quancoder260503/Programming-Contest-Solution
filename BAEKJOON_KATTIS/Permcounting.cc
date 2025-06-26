#include "bits/stdc++.h"

using namespace std; 

const int mod = 76213; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    int n; 
    cin >> n; 
    vector<int64_t>dyn(n + 1);
    dyn[1] = 0; 
    dyn[2] = 1; 
    for(int i = 3; i <= n; i++) { 
        dyn[i] = 1LL * (dyn[i - 1] + dyn[i - 2]) % mod * (i - 1) % mod; 
    }
    cout << dyn[n] << '\n'; 
    return 0; 
}