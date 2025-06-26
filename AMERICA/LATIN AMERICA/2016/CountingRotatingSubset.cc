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
    vector<int>rx(N), ry(N); 
    map<pair<int64_t, int64_t>, int>mp, O; 
    for(int i = 0; i < N; i++) { 
        cin >> rx[i] >> ry[i]; 
        O[{2 * rx[i], 2 * ry[i]}]++; 
    }
    for(int i = 0; i < N; i++) { 
        for(int j = i + 1; j < N; j++) { 
            mp[{rx[i] + rx[j], ry[i] + ry[j]}]++; 
        }
    }
    vector<int64_t>ret(N + 1); 
    ret[0] = N; 
    for(auto [_, ctr] : mp) { 
        for(int i = 1; i <= ctr; i++) { 
            ret[2 * i] += Comb(ctr, i); 
            ret[2 * i] %= mod; 
        }
    }
    for(auto [p, ctr] : O) { 
        for(int i = 0; i <= mp[p]; i++) { 
            ret[2 * i + 1] += Comb(mp[p], i); 
            ret[2 * i + 1] %= mod; 
        }
    }
    for(int i = 1; i <= N; i++) { 
        cout << ret[i] << " "; 
    }
    cout << '\n'; 
    return 0; 
}