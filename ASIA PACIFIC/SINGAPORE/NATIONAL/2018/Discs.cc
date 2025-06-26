#include "bits/stdc++.h"

using namespace std;

#define x first
#define y second

const double INF = 1e100;
const double EPS = 1e-6; 

int main(void) {
    int n; 
    cin >> n; 
    vector<pair<int, int>>p(n); 
    for(int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y; 
    }
    vector<vector<double>>dyn(n, vector<double>(1 << n, INF)); 
    for(int i = 0; i < n; i++) dyn[i][(1 << i)] = 0; 
    for(int mask = 0; mask < (1 << n); mask++) { 
        for(int i = 0; i < n; i++) if(mask & (1 << i)) { 
            for(int j = 0; j < n; j++) if(mask & (1 << j)) {
                double dist = hypot(p[i].x - p[j].x, p[i].y - p[j].y); 
                dyn[i][mask] = min(dyn[i][mask], dyn[j][mask xor (1 << i)] + dist * (__builtin_popcount(mask ^ (1 << i)))); 
            }
        }
    }
    double ret = INF;
    for(int i = 0; i < n; i++) { 
        ret = min(ret, dyn[i][(1 << n) - 1]); 
    }
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0;
}