#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, mx = INT32_MAX;
    cin >> n;
    for (int i = 0, a, b; i < n; i++) { 
        cin >> a >> b;
        mx = min(mx, b / a);
    }
    cout << mx << '\n'; 
    return 0;
}