#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<double> p(n + 1), g(n + 1), dyn(n + 1); 
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    } 
    for (int i = 1; i <= n; i++) {
        g[i] = (1 + g[i - 1]) * p[i]; 
    }
    for (int i = 1; i <= n; i++) {
        dyn[i] = dyn[i - 1] + (2 * g[i - 1] + 1) * p[i]; 
    }
    cout << fixed << setprecision(10) << dyn[n] << '\n'; 
    return 0;
}