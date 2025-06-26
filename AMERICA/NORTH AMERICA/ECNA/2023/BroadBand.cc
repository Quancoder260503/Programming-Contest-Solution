#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout << fixed << setprecision(10); 
    int n, m, k, s; 
    cin >> n >> m >> k >> s;
    n = n + m; 
    vector<double>x(n); 
    for(int i = 0; i < n; i++) { 
        cin >> x[i]; 
    }
    sort(x.begin(), x.end());
    vector<vector<double>>cost(n, vector<double>(n + 1, 0));
    for(int i = 0; i < n; i++) { 
        double x0 = 0, x1 = 0, x2 = 0; 
        for(int j = i; j < n; j++) { 
            x0++; 
            x1 += x[j];
            x2 += x[j] * x[j]; 
            cost[i][j + 1] = -x1 * x1 / x0 + x2; 
        }
    } 
    vector<double>dyn(n + 1, 1e100);
    dyn[0] = 0; 
    for(int _ = 0; _ < k; _++) { 
        vector<double>ndyn(n + 1, 1e100); 
        for(int i = 0; i < n; i++) for(int j = i + 1; j < n + 1; j++) { 
            ndyn[j] = min(ndyn[j], cost[i][j] + dyn[i]); 
        }
        dyn.swap(ndyn); 
    }
    cout << dyn[n] + double(n * s * s) / 4 << '\n'; 
    return 0; 
}