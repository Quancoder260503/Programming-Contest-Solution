#include "bits/stdc++.h"

using namespace std;

#define rep(i, j, k) for (int i = j; i < k; i++)

const int mod = 1e9 + 7;

template <class T, int N>
struct Matrix
{
    typedef Matrix M;
    array<array<T, N>, N> d{};
    M operator*(const M &m) const
    {
        M a;
        rep(i, 0, N) rep(j, 0, N) rep(k, 0, N) a.d[i][j] = (a.d[i][j] + d[i][k] % mod * m.d[k][j] % mod) % mod;
        return a;
    }
    vector<T> operator*(const vector<T> &vec) const
    {
        vector<T> ret(N);
        rep(i, 0, N) rep(j, 0, N) ret[i] = (ret[i] + d[i][j] % mod * vec[j] % mod) % mod;
        return ret;
    }
    M operator^(int64_t p) const
    {
        assert(p >= 0);
        M a, b(*this);
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
    friend ostream &operator<<(ostream &os, M p)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                os << p.d[i][j] << " ";
            }
            os << '\n';
        }
        return os;
    }
};

int main(void)
{
    int n, b, k, x;
    cin >> n >> b >> k >> x;
    vector<int> ctr(10);
    for (int i = 0, t = 0; i < n; i++)
    {
        cin >> t;
        ctr[t]++;
    }
    Matrix<int64_t, 100> dyn;
    for (int i = 0; i < x; i++) for (int j = 0; j < 10; j++) {
        dyn.d[i][(10 * i + j) % x] += ctr[j];
    }
    auto mat = dyn ^ b;
    cout << mat.d[0][k] << '\n';
    return 0;
}