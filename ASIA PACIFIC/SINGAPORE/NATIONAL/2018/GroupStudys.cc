#include "bits/stdc++.h"

using namespace std;

int main(void) {
    int n, m; 
    cin >> n >> m;
    vector<int>a(n); 
    for(int i = 0; i < n; i++) cin >> a[i];
    int64_t mx = 0, mn = 0;
    if(n <= m) { 
        for(int i = 0; i < n; i++) mn += a[i]; 
        mx = mn; 
    }
    else { 
        sort(a.begin(), a.end()); 
        for(int i = 0; i < m; i++) mn += a[i]; 
        int sz = 0; 
        for(int i = 0; i < n % m; i++) { 
            mx += a[sz]; 
            sz += n / m + 1;
        } 
        for(int i = n % m; i < m; i++) { 
            mx += a[sz]; sz += n / m;  
        } 
    }
    cout << mn << " " << mx << '\n'; 
    return 0;
}