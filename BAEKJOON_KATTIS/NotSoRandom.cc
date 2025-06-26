#include "bits/stdc++.h"

using namespace std; 

const int LOG = 31; 

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.tie(NULL); 
    int tc, a, b, c, n, x, k; 
    cin >> tc;
    cout << fixed << setprecision(10); 
    for(int _ = 0; _ < tc; _++) { 
        cin >> n >> x >> k >> a >> b >> c; 
        double ret = 0; 
        for(int bit = 0; bit < LOG; bit++) {
            vector<vector<double>> dyn(n + 1, vector<double>(2)); 
            ((x >> bit) & 1 ? dyn[0][1] : dyn[0][0]) = 1.0; 
            for(int i = 1; i <= n; i++) { 
                if((k >> bit) & 1) {
                    dyn[i][1] = dyn[i - 1][0] * (1.0 * (b + c) / 100) + dyn[i - 1][1] * (1.0 * (a + b) / 100);
                    dyn[i][0] = dyn[i - 1][1] * (1.0 * c / 100) + dyn[i - 1][0] * (1.0 * a / 100);
                }
                else {
                    dyn[i][1] = dyn[i - 1][1] * (1.0 * (b + c) / 100); 
                    dyn[i][0] = dyn[i - 1][0] + dyn[i - 1][1] * (1.0 * a / 100); 
                }
            }
            ret += pow(2, bit) * dyn[n][1]; 
        }
        cout << "Case #" << _ + 1 << ": " << ret << '\n';  
    }
    return 0; 
}