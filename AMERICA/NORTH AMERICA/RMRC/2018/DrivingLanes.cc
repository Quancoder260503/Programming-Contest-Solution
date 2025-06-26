#include "bits/stdc++.h"

using namespace std; 

const int64_t oo = LLONG_MAX / 2; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    int n, m, k, r; 
    cin >> n >> m >> k >> r; 
    vector<int>l(n), c(n), s(n); 
    vector<vector<int64_t>>dyn(n, vector<int64_t>(m + 1, -1)); 
    for(int i = 0; i < n; i++) { 
        cin >> l[i]; 
    }
    for(int i = 0; i < n - 1; i++) { 
        cin >> s[i] >> c[i]; 
    }
    function<int64_t(int, int)> memo = [&](int line, int lane) -> int64_t { 
        if(line == n) return (lane == 1) ? 0 : oo; 
        int64_t &ret = dyn[line][lane]; 
        if(ret != -1) return ret;
        ret = oo; 
        for(int x = 0; x <= m; x++) { 
            if(lane + x <= m && k * x <= l[line]) { ret = min(ret, memo(line + 1, lane + x) + (line < n - 1 ? s[line] + c[line] * (lane + x) : 0) + l[line] + x * r); }
            if(lane - x  > 0 && k * x <= l[line]) { ret = min(ret, memo(line + 1, lane - x) + (line < n - 1 ? s[line] + c[line] * (lane - x) : 0) + l[line] + x * r); }
        }
        return ret; 
    }; 
    cout << memo(0, 1) << '\n'; 
    return 0; 
}