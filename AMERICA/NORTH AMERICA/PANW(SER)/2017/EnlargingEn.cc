#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n, x; 
    cin >> n >> x; 
    vector<int>p(n); 
    for(int i = 0; i < n; i++) { 
        cin >> p[i]; 
    }
    sort(p.begin(), p.end()); 
    vector<vector<vector<int64_t>>>dyn(n, vector<vector<int64_t>>(1 << n, vector<int64_t>(x + 1))); 
    for(int mask = 0; mask < (1 << n); mask++) { 
        if(__builtin_popcount(mask) == 1) { 
            for(int pos = n - 1; pos >= 0; pos--) if(mask & (1 << pos)) { 
                if(pos == n - 1) continue; 
                int px = (p[n - 1] - p[pos] + 1) * n; 
                if(px <= x) { 
                    dyn[pos][mask][px] = 1;
                }
                break; 
            }
            continue; 
        }
        for(int nxt = 0; nxt < n; nxt++) if((mask & (1 << nxt))) { 
            for(int pre = 0; pre < n; pre++) if(pre != nxt && mask & (1 << pre)) {
                int px = max(0, p[pre] - p[nxt] + 1) * (n - __builtin_popcount(mask) + 1); 
                for(int nx = 0; nx + px <= x; nx++) { 
                    dyn[nxt][mask][nx + px] += dyn[pre][mask ^ (1 << nxt)][nx]; 
                }
            } 
        } 
    }
    int64_t ret = 0; 
    for(int i = 0; i < n; i++)
    for(int j = 0; j <= x; j++) { 
        ret += dyn[i][(1 << n) - 1][j]; 
    }
    cout << ret << '\n'; 
    return 0; 
}

/* 
   dp(mask, x, y) = {number of ways to assign score, mask represent the number of people have been assigned score with
                     the last singer be x, the  number of remaing points is y}
*/ 