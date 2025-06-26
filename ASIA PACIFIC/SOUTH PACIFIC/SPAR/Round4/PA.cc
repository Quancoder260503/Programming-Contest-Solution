#include "bits/stdc++.h"

using namespace std; 

#define double long double
const int L = 200; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n, r, m; 
    cin >> n >> r >> m;
    vector<int>t(m + 2), d(m + 2); 
    vector<double>p(m + 2);
    for(int i = 1; i <= m; i++) { 
        cin >> t[i] >> p[i] >> d[i]; 
    }
    p[m + 1] = p[0] = 1.0; 
    t[m + 1] = n; 
    int rem = r - n; 
    auto f = [&](double P) { 
        vector<vector<double>>dyn(m + 2, vector<double>(rem));
        for(int i = m; i >= 0; i--) { 
            for(int j = 0; j < rem; j++) { 
                double cost = (j + d[i] < rem ? min(P, dyn[i + 1][j + d[i]] + t[i + 1] - t[i] + d[i]) : P); 
                dyn[i][j] = (dyn[i + 1][j] + t[i + 1] - t[i]) * p[i] + (1.0 - p[i]) * cost; 
            }
        } 
        return dyn[0][0] > P; 
    }; 
    double left = 0.0, right = 1e12L; 
    for(int i = 0; i < L; i++) { 
        double middle = (left + right) / 2; 
        if(f(middle)) left = middle;
        else right = middle; 
    }
    cout << fixed << setprecision(10) << left << '\n'; 
    return 0; 
}