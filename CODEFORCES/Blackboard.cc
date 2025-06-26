#include "bits/stdc++.h"
using namespace std;
#define Lint long long
const int mod = 1e9 + 7;
const int M = 1e5 + 7; 
template <int MD>
struct ModInt
{
    int x;

    constexpr ModInt() : x(0) {}
    constexpr ModInt(Lint v) { _set(v % MD + MD); }
    constexpr static int mod() { return MD; }
    constexpr explicit operator bool() const { return x != 0; }

    constexpr ModInt operator+(const ModInt &a) const
    {
        return ModInt()._set((Lint)x + a.x);
    }
    constexpr ModInt operator-(const ModInt &a) const
    {
        return ModInt()._set((Lint)x - a.x + MD);
    }
    constexpr ModInt operator*(const ModInt &a) const
    {
        return ModInt()._set((Lint)x * a.x % MD);
    }
    constexpr ModInt operator/(const ModInt &a) const
    {
        return ModInt()._set((Lint)x * a.inv().x % MD);
    }
    constexpr ModInt operator-() const
    {
        return ModInt()._set(MD - x);
    }

    constexpr ModInt &operator+=(const ModInt &a) { return *this = *this + a; }
    constexpr ModInt &operator-=(const ModInt &a) { return *this = *this - a; }
    constexpr ModInt &operator*=(const ModInt &a) { return *this = *this * a; }
    constexpr ModInt &operator/=(const ModInt &a) { return *this = *this / a; }

    friend constexpr ModInt operator+(Lint a, const ModInt &b)
    {
        return ModInt()._set(a % MD + b.x);
    }
    friend constexpr ModInt operator-(Lint a, const ModInt &b)
    {
        return ModInt()._set(a % MD - b.x + MD);
    }
    friend constexpr ModInt operator*(Lint a, const ModInt &b)
    {
        return ModInt()._set(a % MD * b.x % MD);
    }
    friend constexpr ModInt operator/(Lint a, const ModInt &b)
    {
        return ModInt()._set(a % MD * b.inv().x % MD);
    }

    constexpr bool operator==(const ModInt &a) const { return x == a.x; }
    constexpr bool operator!=(const ModInt &a) const { return x != a.x; }

    friend std::istream &operator>>(std::istream &is, ModInt &x)
    {
        Lint val;
        is >> val;
        x = ModInt(val);
        return is;
    }
    constexpr friend std::ostream &operator<<(std::ostream &os, const ModInt &x)
    {
        return os << x.x;
    }

    constexpr ModInt pow(Lint k) const
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
                for (Lint i = 2; i * i <= v; i++)
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
    constexpr inline __attribute__((always_inline)) ModInt &_set(Lint v)
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
using mint = ModInt<mod>;
signed main(void)
{
    Lint N, K; 
    while(cin >> N >> K)
    {
        auto doit = [&](mint p, int n, int k)
        { 
            vector<vector<mint>>dyn(k + 1, vector<mint>(n + 1)); 
            dyn[0][n] = 1; 
            for(int i = 0; i < k; i++)
            {
                for(int j = 0; j <= n; j++)
                {
                    for(int t = 0; t <= j; t++)
                    {
                        dyn[i + 1][t] = dyn[i + 1][t] + dyn[i][j] * ((mint)(j + 1)).pow(mod - 2); 
                    }
                }
            }
            mint ret = 0;
            mint num = 1; 
            for(int i = 0; i <= n; i++)
            {
                ret = ret + dyn[k][i] * num; 
                num = num * p; 
            }
            return ret; 
        }; 
        mint ret = 1; 
        for(int Lint i = 2; i * i <= N; i++)
        {
            if(N % i == 0) 
            { 
                int D = 0;
                while(N % i == 0)
                {
                    D++;
                    N = N / i; 
                }
                ret = ret * doit(i, D, K); 
            } 
        }
        if(N > 1)
        {
            ret = ret * doit(N, 1, K); 
        }
        cout << ret << '\n'; 
    }   
    return 0; 
}