#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int n; 
    cin >> n; 
    double x, y, ret = 0; 
    for(int i = 0; i < n; i++) { 
        cin >> x >> y;
        ret += x * y; 
    }
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0; 
}