#include "bits/stdc++.h"

using namespace std;

#define double long double 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n;
    string a, b; 
    cin >> a >> b;  
    vector<vector<double>>dyn(n, vector<double>(26)), dyn2(n, vector<double>(26)); 
    for(int i = 0; i < n; i++) {
        if(i) dyn[i] = dyn[i - 1], dyn2[i] = dyn2[i - 1]; 
        dyn[i][a[i] - 'A']  += (i + 1); 
        dyn2[i][b[i] - 'A'] += (i + 1);
    }
    double ret = 0; 
    double den = 1.0 * n * (n + 1) * (2 * n + 1) / 6.0; 
    for(int i = 0; i < n; i++) { 
        ret += dyn[i][b[i] - 'A']  * (n - i) / den; 
        if(i) ret += dyn2[i - 1][a[i] - 'A'] * (n - i) / den; 
    }
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0; 
}

/*
   Linerity of Expectation
*/ 