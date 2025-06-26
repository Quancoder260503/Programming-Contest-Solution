#include "bits/stdc++.h"

using namespace std;

#define sz(a) int(a.size())
#define int64_t long long

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n, v; 
    cin >> n >> v; 
    vector<int64_t>a(n), b(n); 
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    for(int i = 0; i < n; i++) { 
        cin >> b[i]; 
    }
    vector<int>ord(n);
    iota(ord.begin(), ord.end(), 0); 
    vector<int64_t>lis; 
    sort(ord.begin(), ord.end(), [&](int x, int y){     
        if (1LL * a[x] * v + b[x] == 1LL * a[y] * v + b[y]) { 
            return 1LL * a[x] * v - b[x] < 1LL * a[y] * v - b[y];
        }  
        return 1LL * a[x] * v + b[x] < 1LL * a[y] * v + b[y];
    }); 
    for(int i = 0; i < n; i++) {
        int k = ord[i]; 
        if (1LL * a[k] * v + b[k] < 0 || 1LL * a[k] * v - b[k] < 0) continue;
        int pos = lower_bound(lis.begin(), lis.end(), 1LL * a[k] * v - b[k] + 1) - lis.begin(); 
        if(pos == sz(lis)) { 
            lis.push_back(1LL * a[k] * v - b[k]); 
        }
        else { 
            lis[pos] = 1LL * a[k] * v - b[k]; 
        }
    }
    cout << sz(lis) << '\n'; 
    return 0; 
}