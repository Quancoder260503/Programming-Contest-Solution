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
    int N, M; 
    cin >> N >> M;
    cout << Comb(2 * M + N - 1, N - 1) << '\n'; 
    return 0;
}