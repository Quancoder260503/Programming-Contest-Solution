#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int n, h; 
/* 
int f(int i, int j) { 
    if(i < n && j == 0) return 0; 
    if(i >= n) return (j == 0); 
    if(dyn[i].count(j)) return dyn[i][j]; 
    for(int k = 1; k * C[n - 1][i] <= j; k++) { 
        if(f(i + 1, j - k * C[n - 1][i])) { 
            par[i][j] = k; 
            return dyn[i][j] = true; 
        }
    }
    return dyn[i][j] = false; 
}
*/ 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> h;  
    /* 
    C[0][0] = 1; 
    for(int i = 1; i < maxf; i++) { 
        for(int j = 0; j <= i; j++) { 
            C[i][j] = C[i - 1][j] + (j ? C[i - 1][j - 1] : 0);
        }
    }
    */ 
    if(h >= (1 << (n - 1))) {
        vector<int>ret;  
        for(int i = 0; i < n - 1; i++) { 
            ret.push_back(1); 
        }
        ret.push_back(h - (1 << (n - 1)) + 1); 
        vector<vector<int>>ans;
        ans.push_back(ret); 
        for(int i = 0; i < n - 1; i++) { 
            vector<int>nret; 
            for(int i = 0; i + 1 < sz(ret); i++) { 
                nret.push_back(ret[i] + ret[i + 1]); 
            }
            ans.push_back(nret); 
            ret.swap(nret); 
        }
        reverse(ans.begin(), ans.end());
        for(auto &x : ans) { 
            for(auto &v : x) cout << v << " "; 
            cout << '\n'; 
        }
    }
    else { 
        cout << "impossible\n"; 
    }
    return 0; 
}