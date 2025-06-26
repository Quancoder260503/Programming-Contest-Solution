#include "bits/stdc++.h"

using namespace std; 

const int mod = 1e9 + 7;


int64_t Comb(int a, int b) { 
    #define COMB_MAXA 5000
    #define COMB_MAXB 5000
    static int64_t combmemo[COMB_MAXA + 1][COMB_MAXB + 1]; 
    if(a < b || b < 0) return 0; 
    if(!a) return 1;
    int64_t &ret = combmemo[a][b]; 
    if(!ret) ret = (Comb(a - 1, b - 1) + Comb(a - 1, b)) % mod; 
    return ret; 
}

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int N; 
    cin >> N; 
    vector<int>c(N); 
    for(int i = 0; i < N; i++) { 
        cin >> c[i]; 
    }
    int64_t ret = 1; 
    int total = 0; 
    for(int i = 0; i < N; i++) { 
        ret = ret % mod * Comb(total + c[i] - 1, c[i] - 1) % mod; 
        total += c[i]; 
    }
    cout << ret << '\n'; 
    return 0; 
}