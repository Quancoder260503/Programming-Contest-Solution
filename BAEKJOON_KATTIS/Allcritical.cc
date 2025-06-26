#include "bits/stdc++.h"

using namespace std;

const int LIM = 2100; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    vector<vector<double>> c(30, vector<double>(30));
    c[0][0] = 1;
    for (int i = 1; i < 30; i++) for (int j = 0; j <= i; j++) { 
        c[i][j] = c[i - 1][j] + (j ? c[i - 1][j - 1] : 0); 
    }
    int tc;
    cin >> tc;
    cout << fixed << setprecision(5);
    for (int _ = 0; _ < tc; _++) {
        cout << "Case #" << _ + 1 << ": "; 
        double p;
        cin >> p;
        vector<vector<double>> dyn(20 + 1, vector<double>(LIM + 1));
        dyn[0][0] = 1;
        for (int j = 1; j <= LIM; j++) for(int i = 0; i <= 20; i++) for(int k = 0; k <= i; k++) { 
            dyn[i][j] += dyn[i - k][j - 1] * c[20 + k - i][k] * pow(p, k) * pow(1.0 - p, 20 - i) ; 
        }
        double ret = 0;
        for (int i = 1; i <= LIM; i++) {
            ret += i * (dyn[20][i] - dyn[20][i - 1]); 
        }
        cout << ret << '\n';
    }
    return 0;
}