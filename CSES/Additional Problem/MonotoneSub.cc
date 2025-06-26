#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int tc, n, k; 
    cin >> tc; 
    for(int _ = 0; _ < tc; _++) { 
        cin >> n >> k; 
        if(1LL * k * k < n) { 
            cout << "IMPOSSIBLE\n"; 
            continue; 
        }
        int l = 1, r = k; 
        vector<int>ret; 
        while(true) { 
            for(int i = r; i >= l; i--) ret.push_back(i);
            if(r == n) break; 
            l = r + 1; 
            r = min(r + k, n); 
        }
        for(auto r : ret) cout << r << " "; 
        cout << '\n'; 
    } 
    return 0; 
}