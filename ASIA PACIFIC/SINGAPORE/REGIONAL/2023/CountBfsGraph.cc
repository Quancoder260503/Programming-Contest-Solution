#include "bits/stdc++.h"
 
using namespace std;
 
const int mod = 998244353;  
const int N = 5010; 
 
int64_t dyn[N][N][2], a[N], p[N];  
int n; 
 
int64_t memo(int i, int j, int k) { 
    if(j == 0) return 0;
    if(i == n) return 1; 
    int64_t &ret = dyn[i][j][k];
    if(ret != -1) return ret; 
    ret = memo(i, j - 1, true);
    if(k || a[i] > a[i - 1]) { 
        ret += memo(i + 1, j + 1, false) % mod * p[j - 1] % mod; 
        ret %= mod; 
    } 
    return ret; 
}  
 
int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    cin >> n; 
    p[0] = 1;
    for(int i = 1; i < N; i++) { 
        p[i] = p[i - 1] * 2 % mod; 
    }
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    memset(dyn, -1, sizeof(dyn)); 
    cout << memo(1, 1, true) << '\n'; 
    return 0;
}