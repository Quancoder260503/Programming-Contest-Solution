#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 3e5 + 2;
const int LOG = 20; 
const int64_t INF = 1e12; 

int64_t dynL[2][maxf][LOG], dynR[2][maxf][LOG], dyncL[LOG][2], dyncR[LOG][2]; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    int n, k; 
    cin >> n >> k; 
    memset(dynL, -1, sizeof(dynL)); 
    memset(dynR, -1, sizeof(dynR)); 
    for(int i = 0; i < LOG; i++)
    for(int j = 0; j < 2; j++) { 
        dyncL[i][j] = dyncR[i][j] = -INF; 
    }
    vector<int64_t>left, right; 
    function<int64_t(int, int, int, int)> func = [&](int pos, int skips, int finish, int side) -> int64_t {
        if(pos == -1) return (skips == 0 ? 0 : -INF); 
        if(skips < 0) return -INF; 
        int64_t &ret = (side ? dynR : dynL)[finish][pos][skips];
        if(ret != -1) return ret; 
        ret = -INF; 
        ret = max(ret, func(pos - 1, skips, finish, side) + (side ? right : left)[pos]);
        ret = max(ret, func(pos - 1, skips - 1, finish, side));
        if(skips == 0 && finish) ret = max(ret, 0LL); 
        return ret;  
    }; 
    for(int iter = 0, x; iter < n; iter++) {
        char c; cin >> c; 
        if(c == 'M') { 
            int64_t ret = 0; 
            ret = max(ret, dyncL[k][1]); 
            ret = max(ret, dyncR[k][1]); 
            for(int i = 0; i <= k; i++) {
                ret = max(ret, dyncL[i][0] + dyncR[k - i][0]);
            }
            cout << ret << '\n'; 
        }
        else if(c == 'L') {
            cin >> x;  
            left.push_back(x); 
            for(int i = 0; i <= k; i++) for(int j = 0; j < 2; j++) {
                dyncL[i][j] = max(dyncL[i][j], func(sz(left) - 1, i, j, false)); 
            }
        }
        else { 
            cin >> x;  
            right.push_back(x); 
            for(int i = 0; i <= k; i++) for(int j = 0; j < 2; j++) { 
                dyncR[i][j] = max(dyncR[i][j], func(sz(right) - 1, i, j, true)); 
            }
        }
    }
    return 0; 
} 
