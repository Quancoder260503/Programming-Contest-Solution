#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    int n; 
    int64_t c, d; 
    cin >> n >> c >> d; 
    vector<int64_t>a(n), psum(n + 1);
    for(int i = 0; i < n; i++) { 
        cin >> a[i];
        psum[i + 1] = psum[i] + a[i]; 
    }
    int64_t sum = psum.back(); 
    sum = abs(sum);
    int64_t ret = INT64_MAX; 
    for(int i = 0; i <= n; i++) { 
        if(c + psum[i] < d) continue; 
        int64_t x = floor(1.0 * (c - d + psum[i]) / sum);
        if(c - x * sum + psum[i] >= d) ret = min(ret, c - x * sum + psum[i]); 
    }
    cout << (ret == INT64_MAX ? -1 : ret) << '\n'; 
    return 0; 
}