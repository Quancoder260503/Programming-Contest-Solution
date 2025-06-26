#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int tc;
    cin >> tc;
    for(int _ = 0, n, k; _ < tc; _++) { 
        cin >> n >> k; 
        vector<int>a(n), b(n), c(n), d(n); 
        for(int i = 0; i < n; i++) cin >> a[i];
        for(int i = 0; i < n; i++) cin >> b[i];
        for(int i = 0; i < n; i++) cin >> c[i];
        for(int i = 0; i < n; i++) cin >> d[i]; 
        map<int, int64_t>ctrl, ctrr;
        for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) { 
            ctrl[a[i] ^ b[j]]++;
            ctrr[c[i] ^ d[j]]++; 
        }
        int64_t ret = 0;
        for(const auto &[u, v] : ctrl) { 
            ret += 1LL * v * ctrr[k ^ u]; 
        }
        cout << "Case #" << _ + 1 << ": " << ret << '\n'; 
    }
    return 0; 
}