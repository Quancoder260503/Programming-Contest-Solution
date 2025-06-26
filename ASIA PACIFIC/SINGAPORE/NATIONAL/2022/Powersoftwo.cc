#include "bits/stdc++.h"

using namespace std; 

const int moda = 1e9 + 7; 
const int modb = 998244353;  

int64_t fpow(int64_t a, int64_t k, int mod) {
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k) {
        if (k & 1) {
            res = (int64_t)res * tmp % mod;
        }
        tmp = (int64_t)tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    int n; 
    cin >> n;
    int64_t reta = 0, retb = 0;  
    for(int i = 0; i < n; i++) { 
        char c; int x;  
        cin >> c >> x; 
        if(c == '+') { 
            reta = (reta + fpow(2, x, moda)) % moda; 
            retb = (retb + fpow(2, x, modb)) % modb; 
        }
        else { 
            reta = (reta + moda - fpow(2, x, moda)) % moda; 
            retb = (retb + modb - fpow(2, x, modb)) % modb; 
        }
        cout << (reta == 0 && retb == 0 ? "YES" : "NO") << '\n'; 
    } 
    return 0;  
}