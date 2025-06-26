#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int tc;
    cin >> tc;
    for (int _ = 0, n, q; _ < tc; _++) {
        cin >> n >> q;
        vector<int>a(n); 
        for(int i = 0; i < n; i++) cin >> a[i]; 
        vector<int>psum(n + 1);
        vector<int64_t>qsum(n + 1); 
        for(int i = 0; i < n; i++) { 
            psum[i + 1] = psum[i] + a[i];
            qsum[i + 1] = qsum[i] + 1LL * i * a[i];
        }
        auto get_sub = [&](int64_t x) { 
            int64_t ret = 0; 
            int ptr = 0; 
            for(int i = 0; i <= n; i++) {
                while(ptr < n && psum[ptr + 1] - psum[i] <= x) ptr++; 
                if(psum[ptr] - psum[i] <= x) ret += (ptr - i);
            }
            return ret; 
        };
        auto f = [&](int64_t x) {
            int64_t l = 0, r = psum[n];
            while (l <= r) {
                int64_t mid = (r - l) / 2 + l;
                if (get_sub(mid) < x) l = mid + 1; 
                else r = mid - 1; 
            }
            return l; 
        };
        auto calc = [&](int64_t x, int64_t r) {
            int64_t ret = 0, total = 0;
            int ptr = 0; 
            for (int i = 0; i <= n; i++) {
                while (ptr < n && psum[ptr + 1] - psum[i] <= x) ptr++;
                if (psum[ptr] - psum[i] <= x) { 
                    total += (ptr - i); 
                    ret += 1LL * ptr * (psum[ptr] - psum[i]) - (qsum[ptr] - qsum[i]);
                } 
            }
            ret -= 1LL * (total - r) * x; 
            return ret;
        };
        cout << "Case #" << _ + 1 << ":\n";
        for(int i = 0; i < q; i++) { 
            int64_t l, r; 
            cin >> l >> r; 
            int64_t a = f(l - 1), b = f(r); 
            cout << calc(b, r) - calc(a, l - 1) << '\n'; 
        }
    }
    return 0;
}