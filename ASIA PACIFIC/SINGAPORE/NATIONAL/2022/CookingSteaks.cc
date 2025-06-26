#include "bits/stdc++.h"

using namespace std;

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> c(n - 1), a(n), b(n);
    for (int i = 0; i < n - 1; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    int64_t ret = 0;
    for (int i = n - 1; i >= 0; i--) { 
        if(a[i] >= b[i]) {
            a[i] = a[i] - b[i];
            continue; 
        }
        if(i == 0) {
            ret = -1;
            break; 
        }
        int cc = b[i] - a[i];
        a[i - 1] -= cc;
        a[i] += cc;
        ret += 1LL * cc * c[i - 1];
    }
    cout << ret << '\n'; 
    return 0;
}