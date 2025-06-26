#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int64_t x, y;
    cin >> x >> y;
    x--, y--;
    int64_t g = gcd(x, y);
    int ret = 0;
    for (int dx = -g; dx <= g; dx++) {
        int64_t dy = sqrt(1LL * g * g - 1LL * dx * dx);
        if (1LL * dx * dx + 1LL * dy * dy == 1LL * g * g) {
            ret++;
        }
    }
    --ret; 
    ret = ret / (x == y ? 2 : 1);
    cout << ret << '\n'; 
    return 0;
}