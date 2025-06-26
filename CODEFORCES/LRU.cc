#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<double>a(n);
    double x;
    int mcount_zero = 0; 
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mcount_zero +=  (a[i] > 0);
    }
    k = min(k, mcount_zero);
    vector<double> dyn((1 << n)), ret(n);
    dyn[0] = 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        int ctr = __builtin_popcount(mask);
        double p = 0; 
        for (int i = 0; i < n; i++) if (!(mask & (1 << i))) {
            p += a[i]; 
        }
        if (ctr == k) {
            for (int i = 0; i < n; i++) if (mask & (1 << i)) {
                ret[i] += dyn[mask];
            }
        } 
        else if (ctr < k && p > 0) {
            for (int i = 0; i < n; i++)
                if (!(mask & (1 << i))) {
                    dyn[mask | (1 << i)] += dyn[mask] * a[i] / p;
            }
        }
    }
    cout << fixed << setprecision(10); 
    for (int i = 0; i < n; i++) cout << ret[i] << " ";
    cout << '\n'; 
    return 0;
}