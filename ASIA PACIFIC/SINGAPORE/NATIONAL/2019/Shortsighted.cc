#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
const int MAX = 1e5 + 10;
int N, Q;
template <int MD>
struct ModInt
{
    using int64_t = long long;
    int x;

    constexpr ModInt() : x(0) {}
    constexpr ModInt(int64_t v) { _set(v % MD + MD); }
    constexpr static int mod() { return MD; }
    constexpr explicit operator bool() const { return x != 0; }

    constexpr ModInt operator+(const ModInt &a) const
    {
        return ModInt()._set((int64_t)x + a.x);
    }
    constexpr ModInt operator-(const ModInt &a) const
    {
        return ModInt()._set((int64_t)x - a.x + MD);
    }
    constexpr ModInt operator*(const ModInt &a) const
    {
        return ModInt()._set((int64_t)x * a.x % MD);
    }
    constexpr ModInt operator/(const ModInt &a) const
    {
        return ModInt()._set((int64_t)x * a.inv().x % MD);
    }
    constexpr ModInt operator-() const
    {
        return ModInt()._set(MD - x);
    }

    constexpr ModInt &operator+=(const ModInt &a) { return *this = *this + a; }
    constexpr ModInt &operator-=(const ModInt &a) { return *this = *this - a; }
    constexpr ModInt &operator*=(const ModInt &a) { return *this = *this * a; }
    constexpr ModInt &operator/=(const ModInt &a) { return *this = *this / a; }

    friend constexpr ModInt operator+(int64_t a, const ModInt &b)
    {
        return ModInt()._set(a % MD + b.x);
    }
    friend constexpr ModInt operator-(int64_t a, const ModInt &b)
    {
        return ModInt()._set(a % MD - b.x + MD);
    }
    friend constexpr ModInt operator*(int64_t a, const ModInt &b)
    {
        return ModInt()._set(a % MD * b.x % MD);
    }
    friend constexpr ModInt operator/(int64_t a, const ModInt &b)
    {
        return ModInt()._set(a % MD * b.inv().x % MD);
    }

    constexpr bool operator==(const ModInt &a) const { return x == a.x; }
    constexpr bool operator!=(const ModInt &a) const { return x != a.x; }

    friend std::istream &operator>>(std::istream &is, ModInt &other)
    {
        int64_t val;
        is >> val;
        other = ModInt(val);
        return is;
    }
    constexpr friend std::ostream &operator<<(std::ostream &os, const ModInt &other)
    {
        return os << other.x;
    }

    constexpr ModInt pow(int64_t k) const
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
                for (int64_t i = 2; i * i <= v; i++)
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
    constexpr inline __attribute__((always_inline)) ModInt &_set(int64_t v)
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
using mint = ModInt<mod>;
mint tree[MAX * 4];
mint lazy[MAX * 4];
mint lazyS[MAX * 4];
mint ctr[MAX * 4]; 
mint prefix[MAX];
void push_down(int p, int l, int mid, int r)
{
    if(lazy[p] != mint(0))
    {
        lazy[2 * p] += lazy[p];
        lazy[2 * p + 1] += lazy[p];
        lazyS[2 * p] += lazyS[p];
        lazyS[2 * p + 1] += lazyS[p];
        ctr[2 * p] += ctr[p]; 
        ctr[2 * p + 1] += ctr[p]; 
        tree[2 * p] += lazy[p] * mint(mid + l) * mint(mid - l + 1) / mint(2) + (prefix[mid] - prefix[l - 1]) * ctr[p] + lazyS[p] * mint(mid - l + 1);
        tree[2 * p + 1] += lazy[p] * mint(r - mid) * mint(r + mid + 1) / mint(2) + (prefix[r] - prefix[mid]) * ctr[p] + lazyS[p] * mint(r - mid);
        lazy[p] = lazyS[p] = ctr[p] = mint(0);
    }
    return;
}
void update(int L, int R, int l = 1, int r = N, int p = 1)
{
    if (L > r || R < l) return;
    if (L <= l && r <= R)
    {
        tree[p]  += mint(R + L) * mint(r + l) * mint(r - l + 1) / mint(2) + prefix[r] - prefix[l - 1] + mint(r - l + 1) * mint(R - L - 1LL * L * R);
        lazy[p]  += mint(R + L);
        lazyS[p] += mint(R - L - 1LL * R * L); 
        ctr[p] += 1; 
        return;
    }
    int mid = (l + r) / 2;
    push_down(p, l, mid, r);
    update(L, R, l, mid, 2 * p);
    update(L, R, mid + 1, r, 2 * p + 1);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}
mint query(int L, int R, int l = 1, int r = N, int p = 1)
{
    if (L > r || R < l) return mint(0);
    if (L <= l && r <= R) return tree[p];
    int mid = (l + r) / 2;
    push_down(p, l, mid, r);
    return query(L, R, l, mid, 2 * p) + query(L, R, mid + 1, r, 2 * p + 1);
}
signed main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> N >> Q)
    {
        for (int i = 1; i <= N; i++) prefix[i] = prefix[i - 1] + mint(1) - mint(i) * mint(i);
        for (int i = 0; i < Q; i++)
        {
            int type, L, R;
            cin >> type >> L >> R;
            if (type == 1)
            {
                update(L, R);
            }
            else
            {
                cout << query(L, R) << '\n';
            }
        }
    }
    return 0;
}
