#include "bits/stdc++.h"

using namespace std;

const int mod = 998244353;
const int maxf = 1002; 

int64_t c[maxf][maxf]; 

int main(void) {
    int n;
    cin >> n;
    c[0][0] = 1; 
    for(int i = 1; i < maxf; i++) for(int j = 0; j <= i; j++){  
        c[i][j] = c[i - 1][j] + (j ? c[i - 1][j - 1] : 0); 
        c[i][j] %= mod; 
    }
    vector<int>arr(n); 
    for(int i = 0; i < n; i++) cin >> arr[i]; 
    int64_t ret = 0; 
    vector<int64_t>dyn(n + 1); 
    dyn[n] = 1; 
    for(int i = n - 1; i >= 0; i--) if(arr[i] > 0)
    {
        for(int j = i + arr[i] + 1; j <= n; j++) { 
            dyn[i] += dyn[j] * c[j - i - 1][arr[i]] % mod;
            dyn[i] %= mod; 
        }
    }
    for(int i = 0; i < n; i++) {
        ret += dyn[i];
        ret %= mod; 
    }
    cout << ret << '\n'; 
    return 0;
}