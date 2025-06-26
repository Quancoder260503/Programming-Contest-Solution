#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int64_t x[3], n = 2, b[3] = {0, 0, 1}, c[6], d;
    cin >> x[1] >> x[0];
    cin >> x[1] >> x[0];
    int s = x[1] + x[0] - 1; 
    while(s) {
        s = s / 2;
        n = n * 2;
    }
    x[2] = n - x[0] - x[1];
    cout << 3 * (__builtin_popcountll(x[0]) + __builtin_popcountll(x[1]) + __builtin_popcountll(x[2]) - 1) << '\n';
    for (int64_t k = n / 2; b[1] < b[2]; k = k / 2) {
        b[0] = b[1];
        b[1] = b[2];
        d = 0;
        for (int i = 0; i < 3; i++) if(x[i] >= k) {
            x[i] -= k;
            c[d++] = i - 2; 
        }
        while(d < 2 * (b[1] - b[0])) c[d++] = b[2]++;
        for (int i = 0; i < b[1] - b[0]; i++) {
            cout << 3 * (b[0] + i) + 1 << " " << 3 * (b[0] + i) + 2 << '\n'; 
            cout << 3 * (b[0] + i)     << " " << (c[2 * i] < 0 ? c[2 * i] : 3 * c[2 * i]) << '\n';
            cout << (c[2 * i + 1] < 0 ? c[2 * i + 1] : 3 * c[2 * i + 1]) << " " << 3 * (b[0] + i) << '\n'; 
        }
    }
    return 0;
}