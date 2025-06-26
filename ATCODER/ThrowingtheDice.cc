#include "bits/stdc++.h"

using namespace std;

int main(void) {    
    ios_base::sync_with_stdio(0); 
    cout.tie(0); 
    cout.tie(0); 
    int n; 
    cin >> n;
    vector<double>dyn(n + 1);  
    dyn[1] = 3.5000000; 
    for(int i = 2; i <= n; i++) {
        dyn[i] = max(1.0, dyn[i - 1]) + max(2.0, dyn[i - 1]) + max(3.0, dyn[i - 1]) + max(4.0, dyn[i - 1]) + max(5.0, dyn[i - 1]) + max(6.0, dyn[i - 1]); 
        dyn[i] = dyn[i] / 6.0; 
    }
    cout << fixed << setprecision(10) << dyn[n] << '\n'; 
    return 0; 
}