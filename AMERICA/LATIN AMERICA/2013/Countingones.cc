#include "bits/stdc++.h"

using namespace std;

const int LOG = 63; 

int64_t Comb(int a, int b) { 
    #define COMB_MAXA LOG + 10
    #define COMB_MAXB LOG + 10
    static int64_t combmemo[COMB_MAXA + 1][COMB_MAXB + 1]; 
    if(a < b || b < 0) return 0; 
    if(!a) return 1;
    int64_t &ret = combmemo[a][b]; 
    if(!ret) ret = Comb(a - 1, b - 1) + Comb(a - 1, b); 
    return ret; 
}

int64_t f(int64_t x) { 
    int64_t ret = 0, ones = 0; 
    for(int i = LOG; i >= 0; i--) {
        if(x & (1LL << i)) { 
            for(int choose = 0; choose <= i; choose++) { 
                ret += Comb(i, choose) * (choose + ones); 
            }
            ones++; 
        }
    }
    ret += ones; 
    return ret; 
}

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int64_t a, b; 
    cin >> a >> b; 
    cout << f(b) - f(a - 1) << '\n'; 
    return 0; 
}
/*
    001 
    010
    011
    100
    101
    110 
    111 
   1000 
   1001
   1010 
   1011
   1100
*/