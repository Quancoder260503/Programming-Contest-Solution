#include "bits/stdc++.h"

using namespace std; 

const int inf = INT32_MAX; 
const int N = 1e5 + 10;
const int M = 102; 

int dyn[M][N], dyn2[M][N]; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0);  
    int n, m; 
    cin >> n; 
    vector<int>a(n + 1); 
    int suma = 0, sumb = 0; 
    for(int i = 1; i <= n; i++) { 
        cin >> a[i]; 
        suma += a[i]; 
    }
    cin >> m; 
    vector<int>b(m + 1); 
    for(int i = 1; i <= m; i++) { 
        cin >> b[i]; 
        sumb += b[i]; 
    }
    for(int i = 0; i < M; i++) { 
        for(int j = 0; j < N; j++) dyn[i][j]  = dyn2[i][j] = inf; 
    }
    dyn[0][0] = dyn2[0][0] = 0; 
    for(int i = 1; i <= n; i++) { 
        for(int j = 0; j <= suma; j++) { 
            dyn[i][j] = dyn[i - 1][j]; 
            if(j >= a[i] && dyn[i - 1][j - a[i]] < inf) dyn[i][j] = min(dyn[i][j], dyn[i - 1][j - a[i]] + 1); 
        }
    }
    for(int i = 1; i <= m; i++) { 
        for(int j = 0; j <= sumb; j++) { 
            dyn2[i][j] = dyn2[i - 1][j]; 
            if(j >= b[i] && dyn2[i - 1][j - b[i]] < inf) dyn2[i][j] = min(dyn2[i][j], dyn2[i - 1][j - b[i]] + 1); 
        }
    }
    int ret = inf; 
    for(int i = 1; i <= min(suma, sumb); i++) { 
        if(dyn[n][i] == inf || dyn2[m][i] == inf) continue; 
        ret = min(ret, dyn[n][i] + dyn2[m][i]); 
    }
    if(ret == inf) { cout << "impossible\n"; }
    else { cout << ret << '\n'; }
    return 0; 
}