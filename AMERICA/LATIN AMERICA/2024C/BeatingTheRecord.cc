#include "bits/stdc++.h"

using namespace std;

#define double long double

const int LIM = 100;

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, t, s;
    cin >> n >> t >> s;
    vector<vector<double>> p(n, vector<double>(2)), g(n, vector<double>(2)), b(n, vector<double>(2));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> p[i][j] >> g[i][j] >> b[i][j];
        }
    }
    auto f = [&](double P) {
        vector<vector<double>> dyn(n + 1, vector<double>(t + 1, P));
        for (int i = 0; i <= t; i++) {
            dyn[n][i] = 0.0;
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = t - 1; j >= 0; j--) {
                for (int k = 0; k < 2; k++) {
                    double c = 0.0;
                    c += (p[i][k] / 100.0) * min(g[i][k] + (int(g[i][k]) + j < t ? dyn[i + 1][int(g[i][k]) + j] : P), P);
                    c += (1.0 - p[i][k] / 100.0) * min(b[i][k] + (int(b[i][k]) + j < t ? dyn[i + 1][int(b[i][k]) + j] : P), P);
                    dyn[i][j] = min(dyn[i][j], c);
                }
            }
        }
        return (s + dyn[0][s] < P);
    };
    double left = 0;
    double right = 1'000'000'000'000;
    for (int i = 0; i < LIM; i++) {
        double middle = (left + right) / 2;
        if (f(middle))
            right = middle;
        else
            left = middle;
    }
    cout << fixed << setprecision(10) << left << '\n';
    return 0;
}