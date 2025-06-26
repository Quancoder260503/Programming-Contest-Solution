#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int64_t a, b; 
    vector<int64_t>ret; 
    for(int i = 1; i < 64; i++) for(int j = 1; j < 63; j++) for(int k = 1; k < 64; k++) { 
        int ctra = (k + 1) / 2, ctrb = k / 2; 
        if(ctra * i + ctrb * j > 63) break; 
        __int128_t c = 1; 
        c = (c << i) - 1; 
        int64_t sum = 0; 
        for(int p = 0; p < k; p++) { 
            if(p % 2 == 0) { 
                sum = (sum << i) + c; 
            }
            else { 
                sum = (sum << j); 
            }
        }
        if(k > 1 || j == 1) ret.push_back(sum); 
    }
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end()); 
    cin >> a >> b; 
    int res = 0; 
    for(auto c : ret) res += (a <= c && c <= b);
    cout << res << '\n';  
    return 0; 
}