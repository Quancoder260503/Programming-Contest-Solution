#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    int64_t m; 
    cin >> n >> m;
    int g = 1;
    while(1LL * g * (g - 1) / 2 + n - g < m) g++;
    int64_t ret = 0; 
    for(int i = 1; i < g; i++) { 
        ret += 1LL * i * (i - 1) / 2 + 1; 
    }
    for(int rem = 0; rem < n - g; rem++) { 
        ret += m - rem;
    }
    cout << ret << '\n'; 
    return 0;
}