#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

struct Fenwick {
    int N;
    vector<int> bit;
    void init(int _N) {
        N = _N;
        bit.resize(N, 0);
        return; 
    }
    int sum(int i) {
        int c = 0;
        for (++i; i > 0; i -= (i & -i)) {
            c += bit[i]; 
        }
        return c;
    }
    int query(int l, int r) { 
        return sum(r) - sum(l - 1); 
    }
    void upd(int i, int dif) {
        for (++i; i < N; i += (i & -i)) {
            bit[i] = dif + bit[i];
        }
    }
};

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    int n, m, tc;
    cin >> tc; 
    while(tc--) { 
        cin >> n;
        vector<int>p(n), a(n); 
        for(int i = 0; i < n; i++) { 
            cin >> p[i]; 
            --p[i]; a[p[i]] = i + 1; 
        }
        Fenwick fw;
        fw.init(2 * n + 10); 
        fw.upd(a[0], 1);
        fw.upd(a[0] + n, 1);
        int64_t ret = 0;  
        for(int i = 1; i < n; i++) { 
            int pre = a[i - 1], curr = a[i];
            if (pre > curr) curr += n; 
            ret += 1LL * (fw.query(pre, curr) - 1) * (n - i);
            fw.upd(a[i], 1);
            fw.upd(a[i] + n, 1); 
        }
        cout << ret << '\n'; 
    } 
    return 0; 
}