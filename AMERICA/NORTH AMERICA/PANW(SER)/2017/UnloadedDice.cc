#include "bits/stdc++.h"

using namespace std;

#define double long double

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    double ret = 1e100;
    vector<double>p(7);  
    double ev = 0.0; 
    for(int i = 1; i <= 6; i++) { 
        cin >> p[i]; 
        ev += p[i] * i; 
    }
    for(int i = 1; i <= 6; i++) { 
        double cev = ev - p[i] * i; 
        ret = min(ret, fabs(i - (3.5 - cev) / p[i])); 
    }
    cout << fixed << setprecision(3) << ret << '\n'; 
    return 0; 
}