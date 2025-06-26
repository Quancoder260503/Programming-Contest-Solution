#include "bits/stdc++.h"

#pragma GCC target("popcnt")

using namespace std;

template <
    typename T // need to support operators + -
    >
struct Fenwick
{
    Fenwick(int _n) : n(_n), f(_n + 1) {}

    // a[u] += val
    void update(int u, T val)
    {
        assert(0 <= u && u < n);
        ++u;
        for (; u <= n; u += u & -u)
        {
            f[u] += val;
        }
    }

    // return a[0] + .. + a[u-1]
    T get(int u) const
    {
        assert(0 <= u && u <= n);
        T res = 0;
        for (; u > 0; u -= u & -u)
        {
            res += f[u];
        }
        return res;
    }

    // return a[l] + .. + a[r-1]
    T get(int l, int r) const
    {
        assert(0 <= l && l <= r && r <= n);
        if (l == r)
            return 0; // empty
        return get(r) - get(l);
    }

    void reset()
    {
        std::fill(f.begin(), f.end(), T(0));
    }

    int n;
    vector<T> f;
};
// }}}

int main()
{
    int tc; 
    cin >> tc; 
    for(int _ = 0; _ < tc; _++)
    {
        int n, m; 
        cin >> n >> m; 
        int N = n + m + 2; 
        Fenwick<int>fenw(N); 
        vector<int>idx(n + 1); 
        for(int i = 0; i < n; i++) 
        {
            idx[i] = n - i - 1; 
            fenw.update(idx[i], 1); 
        }
        for(int i = 0; i < m; i++)
        {
            int x;
            cin >> x; 
            x--; 
            cout << fenw.get(idx[x] + 1, N) << " "; 
            fenw.update(idx[x], -1);
            idx[x] = n + i;  
            fenw.update(idx[x], 1); 
        }
        cout << '\n'; 
    }
    return 0;
}