#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int d, s, n, k; 
    cin >> n >> k >> d >> s; 
    double average = 1.0 * (d * n - k * s) / (n - k); 
    if(average > 100 || average < 0) { 
        cout << "impossible\n"; 
    }
    else { 
        cout << fixed << setprecision(10) << average << '\n'; 
    }
    return 0; 
}