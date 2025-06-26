#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    int n, k, t;
    cin >> n >> k >> t; 
    vector<int>a(n); 
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    sort(a.begin(), a.end()); 
    if(k == n)           { cout << "0\n";  return 0; }
    if(a[k] != a[k - 1]) { cout << "0\n";  return 0; }
    if(t == 0)           { cout << "-1\n"; return 0; }
    int l, r, i; 
    for(i = k - 1, l = 0; i >= 0 && a[k - 1] == a[i]; i--, l++); 
    for(i = k,     r = 0; i < n  && a[k]     == a[i]; i++, r++); 
    int ret = min(l, r);
    if(a[k] == 0) ret = r; 
    if(a[k] == t) ret = l; 
    cout << ret << '\n'; 
    return 0; 
}