#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    int n; 
    cin >> n; 
    int m = __builtin_popcount(n - 1); 
    int ret = 0; 
    for(int i = 0, a; i < n; i++) { 
        cin >> a;
        int d = __builtin_popcount(n - 1 - i) + __builtin_popcount(i); 
        if(d == m) ret ^= a; 
    }
    cout << ret << '\n'; 
    return 0; 
}