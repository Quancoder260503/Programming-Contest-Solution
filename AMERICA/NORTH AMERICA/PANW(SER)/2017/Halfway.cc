#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int64_t n, m, k; 
    cin >> n;
    k = 1LL * n * (n - 1) / 2; 
    m = (1 - sqrt(0.5)) * n;
    if(m < 0) m = 0; 
    while(m * (m - 1) <= k) m++; 
    cout << n + 1 - m << '\n'; 
    return 0; 
}