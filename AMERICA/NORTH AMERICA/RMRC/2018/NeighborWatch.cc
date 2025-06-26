#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int n, m; 
    cin >> n >> m;
    int64_t ret = 1LL * n * (n + 1) / 2; 
    int last = 0; 
    for(int i = 0, x; i < m; i++) { 
        cin >> x; 
        ret = ret - 1LL * (x - last) * (x - last - 1) / 2; 
        last = x; 
    }
    ret = ret - 1LL * (n - last) * (n - last + 1) / 2;  
    cout << ret << '\n'; 
    return 0; 
}