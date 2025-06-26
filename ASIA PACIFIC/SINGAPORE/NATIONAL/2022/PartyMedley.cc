#include "bits/stdc++.h"

using namespace std;

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ctr = 0, ret = 0; 
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++) if(max({a[i], a[j], a[k]}) - min({a[i], a[j], a[k]}) <= m) {
                    ctr++;
                    ret = max(ret, a[i] + a[j] + a[k]); 
            }
    if(ctr == 0) {
        cout << -1 << '\n'; 
    }
    else {
        cout << ctr << " " << ret << '\n'; 
    }
    return 0;
}