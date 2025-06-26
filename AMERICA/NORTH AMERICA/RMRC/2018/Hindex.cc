#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int n; 
    cin >> n;
    vector<int>a(n);  
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    int lo = 0, hi = 1'000'000'000 + 1; 
    auto f = [&](int x) {
        int ret = 0;  
        for(int i = 0; i < n; i++) { 
            ret += (a[i] >= x); 
        }
        return ret >= x; 
    }; 
    while(lo < hi) { 
        int mid = (lo + hi + 1) / 2; 
        if(f(mid)) lo = mid; 
        else hi = mid - 1; 
    }
    cout << lo << '\n'; 
    return 0; 
}