#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

const int mod = 1e9 + 7; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n, m; 
    cin >> m >> n;
    m = (1 << m); 
    vector<int>a(m), b(n); 
    for(int i = 0; i < m; i++) { 
        cin >> a[i]; 
        --a[i]; 
    }
    function<int64_t(int, int)> func = [&](int l, int r) -> int64_t { 
        if(l + 1 == r) return 1; 
        int mid = (l + r) / 2; 
        int flag = true; 
        for(int i = 0; i < mid - l; i++) flag = flag & (a[l + i] == a[mid + i]); 
        int64_t L = func(l, mid), R = func(mid, r); 
        if(flag) return (L + R) % mod; 
        for(int i = l; i < mid; i++) b[a[i]]++;
        flag = true; 
        for(int i = mid; i < r; i++) { 
            flag = flag & (b[a[i]] == 0);  
        } 
        for(int i = l; i < mid; i++) b[a[i]]--;
        return flag ? 1LL * L * R % mod : 0; 
    }; 
    cout << func(0, m) << '\n'; 
    return 0;
}