#include "bits/stdc++.h"

using namespace std; 

const double eps = 1e-6; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    double a1, p1, a2, p2; 
    cin >> a1 >> p1 >> a2 >> p2; 
    if(a1 * p2 > eps + a2 * a2 * M_PI * p1) { 
        cout << "Slice of pizza\n"; 
    }
    else { 
        cout << "Whole pizza\n"; 
    }
    return 0; 
}