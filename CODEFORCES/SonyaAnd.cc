#include "bits/stdc++.h"

using namespace std;

#define rep(i, j, k) for(int i = j; i < k; i++)

const int mod = 1e9 + 7;

int n, k;

template <class T>
struct Matrix {
    typedef Matrix M;
    vector<vector<T>>d; 
    int N; 
    void init(int _n) { 
        d = vector<vector<T>>(n, vector<T>(n)); 
        N = _n; 
    }
    M operator*(const M &m) const {
        M a;
        a.init(N); 
        rep(i, 0, N) rep(j, 0, N) rep(k, 0, N) { 
            a.d[i][j] += d[i][k] * m.d[k][j] % mod;
            a.d[i][j] %= mod; 
        }
        return a;
    }
    M operator^(int64_t p) const
    {
        assert(p >= 0);
        M a, b(*this);
        a.init(N); 
        rep(i, 0, N) a.d[i][i] = 1;
        while (p)
        {
            if (p & 1)
                a = a * b;
            b = b * b;
            p >>= 1;
        }
        return a;
    }
};

int64_t fpow(int64_t a, int64_t k)
{
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k) {
        if (k & 1) {
            res = (int64_t)res * tmp % mod;
        }
        tmp = (int64_t)tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> n >> k;
    vector<int>a(n); 
    int x = 0; 
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
        x += (a[i] == 0); 
    }
    int y = n - x; 
    int z = 0; 
    for(int i = 0; i < x; i++) { 
        z += (a[i] == 0);
    }
    if(x > y) { 
        swap(x, y);
        z = 0; 
        for(int i = n - 1; i >= n - x; i--) { 
            z += a[i]; 
        }
    }
    Matrix<int64_t>mat; 
    mat.init(x + 1); 
    for(int i = 0; i <= x; i++) { 
        mat.d[i][i] = (1LL * x * (x - 1) / 2 + 1LL * y * (y - 1) / 2 + 1LL * (x - i) * i + 1LL * (x - i) * (y - x + i)) % mod; 
        if(i > 0) mat.d[i][i - 1] = 1LL * (x - i + 1) * (x - i + 1) % mod; 
        if(i < x) mat.d[i][i + 1] = 1LL * (i + 1) * (y - x + i + 1) % mod; 
    }
    auto ret = (mat ^ k); 
    int64_t res = 0;
    for(int i = 0; i <= x; i++) { 
        res = (res + ret.d[i][z]) % mod; 
    }
    res = ret.d[x][z] % mod * fpow(res, mod - 2) % mod; 
    cout << res << '\n'; 
    return 0;
}