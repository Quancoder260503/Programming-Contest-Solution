#include "bits/stdc++.h"

using namespace std; 

const int maxf = 500; 

const int64_t INF = 3e18 + 10; 

int64_t dyn[maxf][maxf][maxf]; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);   
    for(int i = 0; i < maxf; i++) 
    for(int j = 0; j < maxf; j++)
    for(int k = 0; k < maxf; k++) {
        dyn[i][j][k] = -1; 
    }
    int n, m;
    int64_t k; 
    cin >> n >> m >> k;
    vector<int>ret(n, -1);  
    function<int64_t(int, int, int)> func = [&](int pos, int match, int fixed) {
        if(pos == 0) return int64_t(fixed == 0);  
        if(dyn[pos][match][fixed] != -1) return dyn[pos][match][fixed]; 
        int64_t &ret = dyn[pos][match][fixed]; 
        ret = 0; 
        if(match > 0 && fixed > 0) { 
            ret += func(pos - 1, match - 1, fixed - 1); 
        }
        if(match > 1) { 
            int64_t num = func(pos - 1, match - 2, fixed); 
            int64_t den = match - 1;             
            if(num <= INF / den) { 
                ret += 1LL * num * den; 
            }
            else ret += INF; 
            if(ret > INF) ret = INF; 
        }
        if(pos > match) { 
            int64_t num = func(pos - 1, max(0, match - 1), fixed);
            int64_t den = (pos - match);  
            if(num <= INF / den) { 
                ret += 1LL * num * den; 
            } 
            else ret += INF; 
            if(ret > INF) ret = INF; 
        } 
        return ret; 
    };
    auto calc = [&](int c) { 
        vector<int>vis(n, false); 
        int pos;
        for(pos = 0; pos < n; pos++) { 
            if(ret[pos] == -1) break; 
            if(vis[ret[pos]]) return int64_t(0); 
            if(ret[pos] == pos) c--; 
            vis[ret[pos]] = true; 
        }
        if(c < 0) return int64_t(0); 
        int matches = 0, rem = 0; 
        for(; pos < n; pos++) { 
            if(!vis[pos]) matches++; 
            rem++; 
        }
        return func(rem, matches, c); 
    }; 
    k--; 
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) { 
            ret[i] = j;
            int64_t c = int64_t(calc(m)); 
            if(k >= c) { 
                k = k - c; 
            }
            else break;
        }
    }
    vector<int>ctr(n); 
    for(int i = 0; i < n; i++) { 
        if(ctr[ret[i]] > 1) {
            cout << -1 << '\n';
            exit(0); 
        } 
        ctr[ret[i]]++; 
    }
    for(int i = 0; i < n; i++) { 
        cout << ret[i] + 1 << " "; 
    }
    cout << '\n'; 
    return 0;
}