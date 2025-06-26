#include "bits/stdc++.h"

using namespace std; 

const int mod = 1e9 + 7; 
const int maxf = 1e5 + 2; 

int64_t dyn[maxf][2][2]; 
int n, x[maxf], y[maxf], d[maxf]; 

int nand(int a, int b, int s) { 
    if(s == -1) { 
        return !(a & b);  
    }
    return s; 
}


void solve(int u) { 
    if(u == 0) { 
        dyn[u][1][1] = dyn[u][0][0] = 1; 
        return; 
    }
    solve(x[u]);
    solve(y[u]); 
    for(auto ca : {0, 1}) for(auto fa : {0, 1}) for(auto cb : {0, 1}) for(auto fb : {0, 1}) { 
        int cc = nand(cb, ca, -1), fc = nand(fa, fb, d[u]); 
        dyn[u][cc][fc] = (dyn[u][cc][fc] + dyn[x[u]][ca][fa] * dyn[y[u]][cb][fb] % mod) % mod; 
    }
    return; 
}

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> n; 
    for(int i = 1; i <= n; i++) { 
        cin >> x[i] >> y[i] >> d[i]; 
    }
    solve(1); 
    cout << (dyn[1][1][0] + dyn[1][0][1]) % mod << '\n'; 
    return 0;
}