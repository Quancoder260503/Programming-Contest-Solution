#include "bits/stdc++.h"

using namespace std;

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, i, k;
    cin >> n >> i >> k;
    double ret = 0; 
    for (int j = 1; j <= n; j++) {
        ret += (j >= i ? 1.0 * (j + 1) / 2.0 : i) * (pow(1.0 * j / n, k) - pow(1.0 * (j - 1) / n, k)); 
    }
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0;
}