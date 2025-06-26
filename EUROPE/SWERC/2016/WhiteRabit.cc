#include "bits/stdc++.h"

using namespace std;

// ModInt {{{
template <int MD>
struct ModInt
{
    using ll = long long;
    int x;

    constexpr ModInt() : x(0) {}
    constexpr ModInt(ll v) { _set(v % MD + MD); }
    constexpr static int mod() { return MD; }
    constexpr explicit operator bool() const { return x != 0; }

    constexpr ModInt operator+(const ModInt &a) const
    {
        return ModInt()._set((ll)x + a.x);
    }
    constexpr ModInt operator-(const ModInt &a) const
    {
        return ModInt()._set((ll)x - a.x + MD);
    }
    constexpr ModInt operator*(const ModInt &a) const
    {
        return ModInt()._set((ll)x * a.x % MD);
    }
    constexpr ModInt operator/(const ModInt &a) const
    {
        return ModInt()._set((ll)x * a.inv().x % MD);
    }
    constexpr ModInt operator-() const
    {
        return ModInt()._set(MD - x);
    }

    constexpr ModInt &operator+=(const ModInt &a) { return *this = *this + a; }
    constexpr ModInt &operator-=(const ModInt &a) { return *this = *this - a; }
    constexpr ModInt &operator*=(const ModInt &a) { return *this = *this * a; }
    constexpr ModInt &operator/=(const ModInt &a) { return *this = *this / a; }

    friend constexpr ModInt operator+(ll a, const ModInt &b)
    {
        return ModInt()._set(a % MD + b.x);
    }
    friend constexpr ModInt operator-(ll a, const ModInt &b)
    {
        return ModInt()._set(a % MD - b.x + MD);
    }
    friend constexpr ModInt operator*(ll a, const ModInt &b)
    {
        return ModInt()._set(a % MD * b.x % MD);
    }
    friend constexpr ModInt operator/(ll a, const ModInt &b)
    {
        return ModInt()._set(a % MD * b.inv().x % MD);
    }

    constexpr bool operator==(const ModInt &a) const { return x == a.x; }
    constexpr bool operator!=(const ModInt &a) const { return x != a.x; }

    friend std::istream &operator>>(std::istream &is, ModInt &other)
    {
        ll val;
        is >> val;
        other = ModInt(val);
        return is;
    }
    constexpr friend std::ostream &operator<<(std::ostream &os, const ModInt &other)
    {
        return os << other.x;
    }

    constexpr ModInt pow(ll k) const
    {
        ModInt ans = 1, tmp = x;
        while (k)
        {
            if (k & 1)
                ans *= tmp;
            tmp *= tmp;
            k >>= 1;
        }
        return ans;
    }

    constexpr ModInt inv() const
    {
        if (x < 1000111)
        {
            _precalc(1000111);
            return invs[x];
        }
        int a = x, b = MD, ax = 1, bx = 0;
        while (b)
        {
            int q = a / b, t = a % b;
            a = b;
            b = t;
            t = ax - bx * q;
            ax = bx;
            bx = t;
        }
        assert(a == 1);
        if (ax < 0)
            ax += MD;
        return ax;
    }

    static std::vector<ModInt> factorials, inv_factorials, invs;
    constexpr static void _precalc(int n)
    {
        if (factorials.empty())
        {
            factorials = {1};
            inv_factorials = {1};
            invs = {0};
        }
        if (n > MD)
            n = MD;
        int old_sz = factorials.size();
        if (n <= old_sz)
            return;

        factorials.resize(n);
        inv_factorials.resize(n);
        invs.resize(n);

        for (int i = old_sz; i < n; ++i)
            factorials[i] = factorials[i - 1] * i;
        inv_factorials[n - 1] = factorials.back().pow(MD - 2);
        for (int i = n - 2; i >= old_sz; --i)
            inv_factorials[i] = inv_factorials[i + 1] * (i + 1);
        for (int i = n - 1; i >= old_sz; --i)
            invs[i] = inv_factorials[i] * factorials[i - 1];
    }

    static int get_primitive_root()
    {
        static int primitive_root = 0;
        if (!primitive_root)
        {
            primitive_root = [&]()
            {
                std::set<int> fac;
                int v = MD - 1;
                for (ll i = 2; i * i <= v; i++)
                    while (v % i == 0)
                        fac.insert(i), v /= i;
                if (v > 1)
                    fac.insert(v);
                for (int g = 1; g < MD; g++)
                {
                    bool ok = true;
                    for (auto i : fac)
                        if (ModInt(g).pow((MD - 1) / i) == 1)
                        {
                            ok = false;
                            break;
                        }
                    if (ok)
                        return g;
                }
                return -1;
            }();
        }
        return primitive_root;
    }

    static ModInt C(int n, int k)
    {
        _precalc(n + 1);
        return factorials[n] * inv_factorials[k] * inv_factorials[n - k];
    }

private:
    // Internal, DO NOT USE.
    // val must be in [0, 2*MD)
    constexpr inline __attribute__((always_inline)) ModInt &_set(ll v)
    {
        x = v >= MD ? v - MD : v;
        return *this;
    }
};
template <int MD>
std::vector<ModInt<MD>> ModInt<MD>::factorials = {1};
template <int MD>
std::vector<ModInt<MD>> ModInt<MD>::inv_factorials = {1};
template <int MD>
std::vector<ModInt<MD>> ModInt<MD>::invs = {0};
// }}}

using mint = ModInt<13>;

template <typename T>
struct Matrix
{
    int n_row, n_col;
    vector<T> x;

    // accessors
    typename vector<T>::iterator operator[](int r)
    {
        return x.begin() + r * n_col;
    }
    inline T get(int i, int j) const { return x[i * n_col + j]; }
    vector<T> at(int r) const
    {
        return vector<T>{x.begin() + r * n_col, x.begin() + (r + 1) * n_col};
    }

    // constructors
    Matrix() = default;
    Matrix(int _n_row, int _n_col) : n_row(_n_row), n_col(_n_col), x(n_row * n_col) {}
    Matrix(const vector<vector<T>> &d) : n_row(d.size()), n_col(d.size() ? d[0].size() : 0)
    {
        for (auto &row : d)
            std::copy(row.begin(), row.end(), std::back_inserter(x));
    }

    // convert to 2d vec
    vector<vector<T>> vecvec() const
    {
        vector<vector<T>> ret(n_row);
        for (int i = 0; i < n_row; i++)
        {
            std::copy(x.begin() + i * n_col,
                      x.begin() + (i + 1) * n_col,
                      std::back_inserter(ret[i]));
        }
        return ret;
    }
    operator vector<vector<T>>() const { return vecvec(); }

    static Matrix identity(int n)
    {
        Matrix res(n, n);
        for (int i = 0; i < n; i++)
        {
            res[i][i] = 1;
        }
        return res;
    }

    Matrix transpose() const
    {
        Matrix res(n_col, n_row);
        for (int i = 0; i < n_row; i++)
        {
            for (int j = 0; j < n_col; j++)
            {
                res[j][i] = this->get(i, j);
            }
        }
        return res;
    }

    Matrix &operator*=(const Matrix &r) { return *this = *this * r; }
    Matrix operator*(const Matrix &r) const
    {
        assert(n_col == r.n_row);
        Matrix res(n_row, r.n_col);

        for (int i = 0; i < n_row; i++)
        {
            for (int k = 0; k < n_col; k++)
            {
                for (int j = 0; j < r.n_col; j++)
                {
                    res[i][j] += this->get(i, k) * r.get(k, j);
                }
            }
        }
        return res;
    }

    Matrix pow(long long n) const
    {
        assert(n_row == n_col);
        Matrix res = identity(n_row);
        if (n == 0)
            return res;

        bool res_is_id = true;
        for (int i = 63 - __builtin_clzll(n); i >= 0; i--)
        {
            if (!res_is_id)
                res *= res;
            if ((n >> i) & 1)
                res *= (*this), res_is_id = false;
        }
        return res;
    }

    // Gauss
    template <typename T2, typename std::enable_if<std::is_floating_point<T2>::value>::type * = nullptr>
    static int choose_pivot(const Matrix<T2> &mtr, int h, int c) noexcept
    {
        int piv = -1;
        for (int j = h; j < mtr.n_row; j++)
        {
            if (mtr.get(j, c) and (piv < 0 or std::abs(mtr.get(j, c)) > std::abs(mtr.get(piv, c))))
                piv = j;
        }
        return piv;
    }
    template <typename T2, typename std::enable_if<!std::is_floating_point<T2>::value>::type * = nullptr>
    static int choose_pivot(const Matrix<T2> &mtr, int h, int c) noexcept
    {
        for (int j = h; j < mtr.n_row; j++)
        {
            if (mtr.get(j, c) != T(0))
                return j;
        }
        return -1;
    }

    // return upper triangle matrix
    [[nodiscard]] Matrix gauss() const
    {
        int c = 0;
        Matrix mtr(*this);
        vector<int> ws;
        ws.reserve(n_col);

        for (int h = 0; h < n_row; h++)
        {
            if (c == n_col)
                break;
            int piv = choose_pivot(mtr, h, c);
            if (piv == -1)
            {
                c++;
                h--;
                continue;
            }
            if (h != piv)
            {
                for (int w = 0; w < n_col; w++)
                {
                    swap(mtr[piv][w], mtr[h][w]);
                    mtr[piv][w] *= -1; // for determinant
                }
            }
            ws.clear();
            for (int w = c; w < n_col; w++)
            {
                if (mtr[h][w] != 0)
                    ws.emplace_back(w);
            }
            const T hcinv = T(1) / mtr[h][c];
            for (int hh = 0; hh < n_row; hh++)
            {
                if (hh != h)
                {
                    const T coeff = mtr[hh][c] * hcinv;
                    for (auto w : ws)
                        mtr[hh][w] -= mtr[h][w] * coeff;
                    mtr[hh][c] = 0;
                }
            }
            c++;
        }
        return mtr;
    }

    // For upper triangle matrix
    T det() const
    {
        T ret = 1;
        for (int i = 0; i < n_row; i++)
        {
            ret *= get(i, i);
        }
        return ret;
    }

    // return rank of inverse matrix. If rank < n -> not invertible
    int inverse()
    {
        assert(n_row == n_col);
        vector<vector<T>> ret = identity(n_row), tmp = *this;
        int rank = 0;

        for (int i = 0; i < n_row; i++)
        {
            int ti = i;
            while (ti < n_row && tmp[ti][i] == 0)
                ++ti;
            if (ti == n_row)
                continue;
            else
                ++rank;

            ret[i].swap(ret[ti]);
            tmp[i].swap(tmp[ti]);

            T inv = T(1) / tmp[i][i];
            for (int j = 0; j < n_col; j++)
                ret[i][j] *= inv;
            for (int j = i + 1; j < n_col; j++)
                tmp[i][j] *= inv;

            for (int h = 0; h < n_row; h++)
            {
                if (i == h)
                    continue;
                const T c = -tmp[h][i];
                for (int j = 0; j < n_col; j++)
                    ret[h][j] += ret[i][j] * c;
                for (int j = i + 1; j < n_col; j++)
                    tmp[h][j] += tmp[i][j] * c;
            }
        }

        *this = ret;
        return rank;
    }

    // sum of all elements in this matrix
    T sum_all()
    {
        return submatrix_sum(0, 0, n_row, n_col);
    }

    // sum of [r1, r2) x [c1, c2)
    T submatrix_sum(int r1, int c1, int r2, int c2)
    {
        T res{0};
        for (int r = r1; r < r2; ++r)
        {
            res += std::accumulate(
                x.begin() + r * n_col + c1,
                x.begin() + r * n_col + c2,
                T{0});
        }
        return res;
    }
};

const int64_t INF = 1e12;
const int maxf = 2000;

int64_t dyn[maxf][maxf];

void init(void)
{
    for (int i = 0; i < maxf; i++) for (int j = 0; j < maxf; j++)
    {
        dyn[i][j] = INF;
    }
    for(int i = 0; i < maxf; i++) dyn[i][i] = 0; 
    return;
}

int main(void)
{
    init();
    int n, a, r, t;
    cin >> n >> a >> r >> t;
    Matrix<mint> c(t, n * n + 1);
    for (int rs = 0; rs < t; rs++)
    {
        int d, p;
        cin >> d >> p;
        vector<int> cc(p);
        for (int i = 0; i < p; i++)
            cin >> cc[i];
        for (int i = 0; i + 1 < p; i++)
        {
            int u = cc[i] - 1;
            int v = cc[i + 1] - 1;
            if (u > v)
                swap(u, v);
            c[rs][u * n + v] += mint(1);
        }
        c[rs][n * n] = mint(d);
    }
    auto ret = c.gauss();
    for (int i = 0; i < ret.n_row; i++)
    {
        int j, flag = 0;
        for (j = 0; j < ret.n_col - 1; j++)
        {
            if (ret[i][j] != mint(0))
            {
                flag = 1;
                break;
            }
        }
        if (!flag)
            continue;
        int w = (ret[i][n * n] / ret[i][j]).x, u = j % n, v = j / n;
        dyn[u][v] = dyn[v][u] = w;
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (dyn[i][k] == INF || dyn[k][j] == INF) continue;
                dyn[i][j] = min(dyn[i][j], dyn[i][k] + dyn[k][j]);
            }
    cout << dyn[a - 1][r - 1] << '\n';
    return 0;
}