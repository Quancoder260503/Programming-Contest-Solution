#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n, m; 
    cin >> n >> m; 
    vector<int>vec; 
    vector<int64_t>fact(20, 1); 
    for(int i = 1; i < 20; i++) { 
        fact[i] = fact[i - 1] * i; 
    }
    int64_t ret = 0; 
    function<void(int, int)> func = [&](int x, int c) { 
        if(x == n) { 
            vector<int>arr;
            for(int i = 0; i < n; i++) for(int j = 1; j <= vec[i]; j++) { 
                arr.push_back(i); 
            } 
            if(sz(arr) != n) return; 
            vector<int>a(min(n + 1, m), 0), b(min(n + 1, m), 0); 
            for(int i = 0; i < n; i++) { 
                a[arr[i] % m]++, b[vec[i] % m]++; 
            }
            if(a == b) {
                int64_t rsum = 1;  
                for(int i = 0; i < sz(b); i++) { 
                    rsum = rsum * fact[b[i]]; 
                }
                for(int i = 0; i < sz(vec); i++) { 
                    rsum = rsum / fact[vec[i]]; 
                }
                ret += rsum; 
            } 
            return; 
        }
        for(int j = 0; j <= c; j++) { 
            vec.push_back(j); 
            func(x + 1, c - j);
            vec.pop_back(); 
        }
        return; 
    }; 
    func(0, n); 
    cout << ret << '\n'; 
    return 0; 
}