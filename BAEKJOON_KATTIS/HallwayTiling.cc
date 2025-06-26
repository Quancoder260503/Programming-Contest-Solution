#include "bits/stdc++.h"

using namespace std;

#define rep(i, j, k) for (int i = j; i < k; i++)

const int mod = 998244353;

template <class T, int N> struct Matrix {
    typedef Matrix M;
    array<array<int, N>, N> d{0}; 
    M operator*(const M &m) const {
        M a;
        rep(i, 0, N) rep(j, 0, N) rep(k, 0, N) a.d[i][j] = (a.d[i][j] + 1LL * d[i][k] % mod * m.d[k][j] % mod) % mod;
        return a;
    }
    vector<T> operator*(const vector<T> &vec) const {
        vector<T> ret(N);
        rep(i, 0, N) rep(j, 0, N) ret[i] = (ret[i] + d[i][j] % mod * vec[j] % mod) % mod;
        return ret;
    }
    M operator^(int64_t p) const {
        assert(p >= 0);
        M a, b(*this);
        rep(i, 0, N) a.d[i][i] = 1;
        while (p) {
            if (p & 1) a = a * b;
            b = b * b;
            p >>= 1;
        }
        return a;
    }
    friend ostream &operator<<(ostream &os, M p) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                os << p.d[i][j] << " ";
            }
            os << '\n';
        }
        return os;
    }
};

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int64_t n;
    cin >> n;
    Matrix<int64_t, 6> mat;
    mat.d[0][0] = mat.d[0][1] = mat.d[0][2] = mat.d[2][1] = mat.d[3][3] = mat.d[3][4] = mat.d[3][5] = mat.d[5][4] = 1;
    mat.d[1][0] = mat.d[2][0] = mat.d[4][3] = mat.d[5][3] = 2;
    mat.d[5][1] = 3; 
    mat.d[4][0] = mat.d[5][0] = 6;
    vector<int64_t> c = {1, 0, 0, 0, 0, 0};
    auto ret = (mat ^ (n - 1)) * c;
    cout << (ret[3] + ret[4] + ret[5]) % mod << '\n';
    return 0;
}