#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    int n, x; 
    cin >> n >> x;
    vector<vector<int64_t>>dyn(n + 1, vector<int64_t>(2));
    dyn[0][0] = dyn[0][1] = x; 
    for(int i = 1; i <= n; i++) {
        int x, y;
        char c1, c2; 
        cin >> c1 >> x >> c2 >> y;
        dyn[i][1] = max({(c1 == '+' ? x + dyn[i - 1][0] : 1LL * x * dyn[i - 1][0]), 
                         (c2 == '+' ? y + dyn[i - 1][0] : 1LL * dyn[i - 1][0] * y), 
                         (c1 == '+' ? x + dyn[i - 1][1] : 1LL * x * dyn[i - 1][1]), 
                         (c2 == '+' ? y + dyn[i - 1][1] : 1LL * dyn[i - 1][1] * y)}); 
        dyn[i][0] = min({(c1 == '+' ? x + dyn[i - 1][0] : 1LL * x * dyn[i - 1][0]), 
                         (c2 == '+' ? y + dyn[i - 1][0] : 1LL * dyn[i - 1][0] * y),
                         (c1 == '+' ? x + dyn[i - 1][1] : 1LL * x * dyn[i - 1][1]), 
                         (c2 == '+' ? y + dyn[i - 1][1] : 1LL * dyn[i - 1][1] * y)}); 

    } 
    cout << dyn[n][1] << '\n'; 
    return 0; 
}