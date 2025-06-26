#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int64_t x, y, rx, ry, dx, dy; 
    cin >> x >> y >> rx >> ry >> dx >> dy; 
    int64_t g = gcd(x, y); 
    int64_t kx = x / g, ky = y / g; 
    if(rx <= kx && kx <= dx && ry <= ky && ky <= dy) { 
        int64_t k = min(dx / kx, dy / ky) + 1; 
        kx = 1LL * k * kx; 
        ky = 1LL * k * ky; 
    }
    if(x <= kx) { 
        cout << "Yes\n"; 
    }
    else { 
        cout << "No\n" << kx << " " << ky << '\n'; 
    }
    return 0;
}