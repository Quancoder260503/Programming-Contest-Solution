#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n, m; 
    cin >> n >> m; 
    vector<int>a(n); 
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    sort(a.begin(), a.end()); 
    auto f = [&](int k) { 
        vector<int>b(a.begin(), a.begin() + k); 
        int64_t used = 0; 
        if(sz(b) > 1) { b.pop_back(); used++; } 
        if(sz(b) > 0) { b.pop_back(); used++; }
        vector<int>c1, c2; 
        for(int i = 0; i < sz(b); i++) {
            if(b[i] % 3 == 0) {
                used += b[i] / 3; 
            }
            else if(b[i] % 3 == 1) { 
                c1.push_back(b[i]); 
            } 
            else if(b[i] % 3 == 2) { 
                c2.push_back(b[i]); 
            }
        } 
        sort(c1.begin(), c1.end()); 
        sort(c2.begin(), c2.end()); 
        int c = min(sz(c1), sz(c2)); 
        for(int i = 0; i < c; i++) { 
            used += 1LL * (c1[i] + c2[i]) / 3; 
        }
        int l, r; 
        for(l = c, r = sz(c1) - 1; l < r; l++, r--) {
            used += 1LL * (c1[l] + c1[r] + 1) / 3;  
        }
        if(l == r) used += 1LL * (c1[l] + 2) / 3; 
        for(l = c, r = sz(c2) - 1; l < r; l++, r--) {
            used += 1LL * (c2[l] + c2[r] + 2) / 3;  
        }
        if(l == r) used += 1LL * (c2[l] + 1) / 3; 
        return used <= int64_t(m);
    };  
    int left = 1, right = n;
    while(left < right) { 
        int middle = left + (right - left + 1) / 2;
        if(f(middle)) left = middle; 
        else right = middle - 1; 
    } 
    cout << left << '\n'; 
    return 0;
}
