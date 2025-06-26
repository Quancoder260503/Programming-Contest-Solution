#include "bits/stdc++.h"

using namespace std;

struct Tree
{
    typedef int64_t T;
    static constexpr T unit = 0;
    T f(T a, T b) { return a + b; } // (any associative fn)
    vector<T> s;
    int n;
    Tree(int _n = 0, T def = unit) : s(2 * _n, def), n(_n) {}
    void upd(int pos, T val)
    {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e)
    { // query [b, e)
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2)
        {
            if (b % 2)
                ra = f(ra, s[b++]);
            if (e % 2)
                rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
}; 

int main(void)
{
    int tc;
    cin >> tc; 
    for(int _ = 0, n, q; _ < tc; _++) {
        cin >> n >> q;
        vector<int> a(n);
        for(int i = 0; i < n; i++) { 
            cin >> a[i]; 
        }
        vector<Tree>seg(4, Tree(n, 0)); 
        for(int i = 0; i < n; i++) { 
            seg[(i & 1)].upd(i, a[i]); 
            seg[(i & 1) + 2].upd(i, (i + 1) * a[i]); 
        }
        int64_t ret = 0;
        for(int i = 0; i < q; i++) { 
            char c; 
            cin >> c; 
            if(c == 'U') { 
                int u, x; 
                cin >> u >> x;
                --u; 
                a[u] = x; 
                seg[(u & 1)].upd(u, a[u]); 
                seg[(u & 1) + 2].upd(u, a[u] * (u + 1)); 
            }
            else {
                int l, r; 
                cin >> l >> r; 
                --l, --r; 
                ret += seg[(l & 1) + 2].query(l, r + 1) - seg[(1 ^ (l & 1)) + 2].query(l, r + 1) + 1LL * l * (seg[(1 ^ (l & 1))].query(l, r + 1) - seg[(l & 1)].query(l, r + 1));
            }
        }
        printf("Case #%d: %lld\n", _ + 1, ret); 
    }
    return 0;
}