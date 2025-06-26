#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n, k; 
    cin >> n;
    vector<double>p(n + 1);
    for(int i = 1; i <= n; i++) {
        int64_t l, r, ctr; 
        cin >> l >> r; 
        ctr = 0; 
        for(int pw = 0; pw <= 18; pw++) {
            int64_t x = int64_t(pow(10, pw)), y = int64_t(2LL * pow(10, pw)); 
            if(x <= r && r < y) { 
                ctr += r - x + 1; 
                break; 
            }
            else if(r < x) break; 
            ctr += (y - x); 
        }
        --l; 
        for(int pw = 0; pw <= 18; pw++) {
            int64_t x = int64_t(pow(10, pw)), y = int64_t(2LL * pow(10, pw)); 
            if(x <= l && l < y) { 
                ctr -= l - x + 1; 
                break; 
            }
            else if(l < x) break; 
            ctr -= (y - x); 
        }
        p[i] = double(ctr) / (r - l); 
    }
    cin >> k; 
    vector<vector<double>>dyn(n + 1, vector<double>(n + 1)); 
    dyn[0][0] = 1.0; 
    for(int i = 1; i <= n; i++) for(int j = 0; j <= i; j++) { 
        dyn[i][j] = p[i] * (j ? dyn[i - 1][j - 1] : 0) + (1.0 - p[i]) * dyn[i - 1][j]; 
    }
    double ret = 0; 
    k = ceil(double(n * k) / 100); 
    for(int i = k; i <= n; i++) ret += dyn[n][i]; 
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0;
}