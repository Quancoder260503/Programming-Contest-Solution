#include "bits/stdc++.h"

using namespace std;

const int maxf = 5000; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10); 
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    sort(p.begin() + 1, p.end());
    int LOG;
    for (LOG = 0; (1 << LOG) < n; LOG++);
    vector<int> a((1 << LOG)); 
    for (int i = 0; i < (1 << LOG) - n; i++) {
        a[2 * i] = p[i];
    }
    for (int i = (1 << LOG) - n; i < n; i++) {
        a[(1 << LOG) - n + i] = p[i];
    }
    vector<vector<double>> dyn(maxf, vector<double>(maxf));
    function<double(int, int)> memo = [&](int i, int d) -> double {
        if (d < 0) return 1;
        if (a[i] == 0) return 0;
        if (dyn[i][d] > 0) return dyn[i][d];
        double ret = 0;
        int l = ((i >> d) ^ 1) << d, r = l + (1 << d);
        for (int k = l; k < r; k++) ret += memo(k, d - 1) * 1.0 * a[i] / (a[i] + a[k]);
        ret = ret * memo(i, d - 1);
        return dyn[i][d] = ret;  
    };
    cout << memo(0, LOG - 1) << '\n'; 
    return 0;
}