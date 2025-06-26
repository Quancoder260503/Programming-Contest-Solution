#include "bits/stdc++.h"

using namespace std;

const int MAX = 102; 

int64_t Comb(int a, int b) { 
    #define COMB_MAXA 5000
    #define COMB_MAXB 5000
    static int64_t combmemo[COMB_MAXA + 1][COMB_MAXB + 1]; 
    if(a < b || b < 0) return 0; 
    if(!a) return 1;
    int64_t &ret = combmemo[a][b]; 
    if(!ret) ret = Comb(a - 1, b - 1) + Comb(a - 1, b); 
    return ret; 
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int tc, ProbNum, n; 
    cin >> tc;
    vector<int64_t>cache(MAX, -1); 
    while(tc--) { 
        cin >> ProbNum >> n;
        if(cache[n] != -1) { 
            cout << ProbNum << " " << cache[n] << '\n'; 
        }
        else { 
            int64_t ret = 0;  
            for(int x = 0; 4 * x <= n; x++)
            for(int y = 0; 2 * y <= n; y++) if(4 * x + 2 * y == n && x >= y) {
                ret += Comb(x + y, y) * Comb(x + y, y); 
            }
            cout << ProbNum << " " << ret << '\n'; 
            cache[n] = ret; 
        }
    }
    return 0; 
}

