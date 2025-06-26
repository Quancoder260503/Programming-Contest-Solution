#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

int main(void) {
    int n = 3; 
    vector<int>a(n), b(n); 
    int64_t ret = 0; 
    for(int i = 0; i < n; i++) cin >> a[i]; 
    for(int i = 0; i < n; i++) cin >> b[i]; 
    for(int i = 0; i < n; i++) if(a[i] < b[i]) { 
        ret += b[i] - a[i]; 
    }
    cout << ret << '\n'; 
    return 0;
}