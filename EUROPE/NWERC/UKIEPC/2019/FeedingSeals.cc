#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    int64_t n, m; 
    cin >> n >> m;
    vector<int64_t>a(n); 
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    int ret = 0;  
    sort(a.begin(), a.end()); 
    int l = 0, r = n - 1; 
    for(; l <= r;) { 
        if(a[l] + a[r] <= m) { 
            l++, r--;
        }
        else { 
            r--; 
        }
        ret++; 
    }
    cout << ret << '\n'; 
    return 0; 
}