#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n; 
    vector<int>a(n);
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    stack<int>stk;
    vector<int>l(n), r(n);  
    for(int i = 0; i < n; i++) { 
        while(stk.size() && a[stk.top()] >= a[i]) { 
            stk.pop(); 
        }
        l[i] = (stk.size() ? stk.top() : -1); 
        stk.push(i); 
    }
    while(stk.size()) stk.pop(); 
    for(int i = n - 1; i >= 0; i--) { 
        while(stk.size() && a[stk.top()] >= a[i]) { 
            stk.pop(); 
        }
        r[i] = (stk.size() ? stk.top() : n); 
        stk.push(i); 
    }
    pair<int64_t, pair<int, int>>ret; 
    for(int i = 0; i < n; i++) { 
        ret = max(ret, {1LL * (r[i] - l[i] - 1) * a[i], {-(l[i] + 1), -(r[i] - 1)}});
    }
    cout << -ret.second.first + 1 << " " << 1 - ret.second.second << " " << ret.first << '\n'; 
    return 0; 
}