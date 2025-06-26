#include "bits/stdc++.h"

using namespace std;

const double pi = acos(-1); 

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10); 
    vector<double> l(9, 1e9), r(9);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        double x, y, rr;
        cin >> x >> y;
        double angle = atan2(y, x);
        for (int k = 3; k <= 8; k++) {
            double phi = floor(angle * k / (2 * pi)) * 2 * pi / k + pi / k;
            rr = cos(phi) * x + sin(phi) * y;
            l[k] = min(l[k], rr);
            r[k] = max(r[k], rr); 
        }
    }
    pair<double, int> ret;
    for (int k = 3; k <= 8; k++) {
        ret = max(ret, {l[k] / r[k], k});
    }
    cout << ret.second << " " << pow(ret.first, 2) << '\n';
    return 0;
}