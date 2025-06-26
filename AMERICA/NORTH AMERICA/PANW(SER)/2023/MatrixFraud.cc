#include "bits/stdc++.h"

using namespace std; 

const int INF = 1e8; 

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.tie(NULL); 
    int n, m; 
    cin >> n >> m;
    vector<vector<char>>g(n, vector<char>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) { 
            cin >> g[i][j]; 
        }
    } 
    if(n < m) { 
        vector<vector<char>>tg(m, vector<char>(n)); 
        for(int i = 0; i < m; i++) for(int j = 0; j < n; j++) { 
            tg[i][j] = g[j][i]; 
        }
        swap(m, n);
        swap(tg, g); 
    }
    vector<vector<int>> dyn(m, vector<int>(m, INF));
    vector<int> prefix(m + 1, 0);
    for(int i = 0; i < n; i++) { 
        for(int j = 0; j < m; j++) { 
            prefix[j + 1] = prefix[j] + (g[i][j] == '1');  
        }
        vector<vector<int>>ndyn(m, vector<int>(m, INF));
        vector<int>pdyn = dyn[0]; 
        for(int l = 0; l < m; l++) { 
            for(int r = 0; r < m; r++) { 
                pdyn[r] = min(pdyn[r], dyn[l][r]); 
            }
            int opt = pdyn[max(0, l - 1)];
            for(int r = l; r < m; r++) { 
                opt = min(opt, pdyn[r]); 
                if(i == 0) opt = (l == 0 ? 0 : INF);
                ndyn[l][r] = min(ndyn[l][r], opt + (prefix[m] - prefix[r + 1]) + prefix[l] + r - l + 1 - (prefix[r + 1] - prefix[l]));
                ///cout << l << " " << r << " " << opt << " " << (prefix[m] - prefix[r + 1]) + prefix[l] + r - l + 1 - (prefix[r + 1] - prefix[l]) << '\n';
            } 
        }
        dyn.swap(ndyn); 
    }
    int ret = INF; 
    for(int i = 0; i < m; i++) {
        ret = min(ret, dyn[i][m - 1]); 
    }
    cout << ret << '\n'; 
    return 0; 
}