#include "bits/stdc++.h"

using namespace std;

#define double long double

const double epsa = 1.L - 1e-18; 
const double epsb = 1.L + 1e-18;

const double c[3][3] = {{1, sqrtl(2), sqrtl(3)}, 
                        {0.5, 1, 2 * sqrtl(2) / (1 + sqrtl(3))}, 
                        {0.5 / sqrtl(3), 3 / (3 + 2 * sqrtl(3)), 1}}; 


int64_t f(int x, int y, int n) { 
    return int64_t(n * c[x][y] * epsa); 
}

int64_t grundy(int i, int64_t x) { 
    if(i == 0 && x == 1) return 2; 
    return f(i, 2, x); 
}

int64_t inv_grundy(int i, int64_t x) { 
    if(i == 2) return x + 1; 
    if(i == 0 && x == 2) return 1; 
    int64_t y = ceill(x / c[i][2] * epsb); 
    return grundy(i, y) == x ? y : 0; 
}

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n; 
    vector<int64_t>a(n), b(n), c(n); 
    string s;
    int64_t gsum = 0; 
    for(int i = 0; i < n; i++) { 
        cin >> s >> a[i];
        b[i] = (s == "circle" ? 0 : (s == "square" ? 1 : 2)); 
        c[i] = grundy(b[i], a[i]); 
        gsum ^= c[i]; 
    } 
    int64_t ret = 0; 
    for(int i = 0; i < n; i++) { 
        int64_t x = c[i], y = gsum ^ x; 
        if(y >= x) continue; 
        for(int j = 0; j < 3; j++) {
            int ig = inv_grundy(j, y);
            ret += (ig != 0 && ig <= f(b[i], j, a[i])); 
        }
    }
    cout << ret << '\n'; 
    return 0;
}
