#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int64_t> dyn(n + 2, 1e17);
    dyn[1] = 0; 
    for (int i = 1, c; i <= n; i++) {
        cin >> c; 
        dyn[i] += c;
        for (int j = 1, x; j <= min(m, n - i + 1); j++) {
            cin >> x;
            dyn[i + j] = min(dyn[i + j], dyn[i] - x);
        }
    }
    cout << dyn[n + 1] << '\n';
    return 0;
}