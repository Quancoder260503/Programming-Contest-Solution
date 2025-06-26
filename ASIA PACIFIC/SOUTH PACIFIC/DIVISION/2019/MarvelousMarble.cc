#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n; 
    map<int, int>a, b; 
    for(int i = 0, x; i < n; i++) { 
        cin >> x;
        a[x]++; 
    }
    for(int i = 0, x; i < n; i++) { 
        cin >> x;
        b[x]++; 
    }
    int ret = true; 
    for(const auto &[u, v] : a) { 
        ret &= (a[u] == b[u])
    }
    cout << (ret ? "marvelous" : "error") << '\n'; 
    return 0; 
}