#include "bits/stdc++.h"

using namespace std;

template <const int64_t mod, const int64_t maxf>
struct NTT
{
    NTT()
    {
        int64_t k = 0;
        while ((1 << k) < maxf)
            k++;
        bitrev[0] = 0;
        for (int64_t i = 1; i < maxf; i++)
        {
            bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (k - 1));
        }
        int64_t pw = fpow(prt(), (mod - 1) / maxf);
        rts[0] = 1;
        for (int64_t i = 1; i <= maxf; i++)
        {
            rts[i] = (long long)rts[i - 1] * pw % mod;
        }
    }

    vector<int64_t> multiply(vector<int64_t> a, vector<int64_t> b)
    {
        static int64_t fa[maxf], fb[maxf], fc[maxf];
        int64_t na = a.size(), nb = b.size();
        for (int64_t i = 0; i < na; i++)
            fa[i] = a[i];
        for (int64_t i = 0; i < nb; i++)
            fb[i] = b[i];
        multiply(fa, fb, na, nb, fc);
        int64_t k = na + nb - 1;
        vector<int64_t> res(k);
        for (int64_t i = 0; i < k; i++)
            res[i] = fc[i];
        return res;
    }

private:
    int64_t rts[maxf + 1];
    int64_t bitrev[maxf];

    int64_t fpow(int64_t a, int64_t k)
    {
        if (!k)
            return 1;
        int64_t res = a, tmp = a;
        k--;
        while (k)
        {
            if (k & 1)
            {
                res = (long long)res * tmp % mod;
            }
            tmp = (long long)tmp * tmp % mod;
            k >>= 1;
        }
        return res;
    }
    int64_t prt()
    {
        vector<int64_t> dvs;
        for (int64_t i = 2; i * i < mod; i++)
        {
            if ((mod - 1) % i)
                continue;
            dvs.push_back(i);
            if (i * i != mod - 1)
                dvs.push_back((mod - 1) / i);
        }
        for (int64_t i = 2; i < mod; i++)
        {
            int64_t flag = 1;
            for (int64_t j = 0; j < (int64_t)dvs.size(); j++)
            {
                if (fpow(i, dvs[j]) == 1)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
                return i;
        }
        assert(0);
        return -1;
    }
    void dft(int64_t a[], int64_t n, int64_t sign)
    {
        int64_t d = 0;
        while ((1 << d) * n != maxf)
            d++;
        for (int64_t i = 0; i < n; i++)
        {
            if (i < (bitrev[i] >> d))
            {
                swap(a[i], a[bitrev[i] >> d]);
            }
        }
        for (int64_t len = 2; len <= n; len <<= 1)
        {
            int64_t delta = maxf / len * sign;
            for (int64_t i = 0; i < n; i += len)
            {
                int64_t *w = sign > 0 ? rts : rts + maxf;
                for (int64_t k = 0; k + k < len; k++)
                {
                    int64_t &a1 = a[i + k + (len >> 1)], &a2 = a[i + k];
                    int64_t t = (long long)*w * a1 % mod;
                    a1 = a2 - t;
                    a2 = a2 + t;
                    a1 += a1 < 0 ? mod : 0;
                    a2 -= a2 >= mod ? mod : 0;
                    w += delta;
                }
            }
        }
        if (sign < 0)
        {
            int64_t in = fpow(n, mod - 2);
            for (int64_t i = 0; i < n; i++)
            {
                a[i] = (long long)a[i] * in % mod;
            }
        }
    }
    void multiply(int64_t a[], int64_t b[], int64_t na, int64_t nb, int64_t c[])
    {
        static int64_t fa[maxf], fb[maxf];
        int64_t n = na + nb - 1;
        while (n != (n & -n))
            n += n & -n;
        for (int64_t i = 0; i < n; i++)
            fa[i] = fb[i] = 0;
        for (int64_t i = 0; i < na; i++)
            fa[i] = a[i];
        for (int64_t i = 0; i < nb; i++)
            fb[i] = b[i];
        dft(fa, n, 1), dft(fb, n, 1);
        for (int64_t i = 0; i < n; i++)
            fa[i] = (long long)fa[i] * fb[i] % mod;
        dft(fa, n, -1);
        for (int64_t i = 0; i < n; i++)
            c[i] = fa[i];
    }
};

template <typename T>
struct CRT
{
    T res;

    CRT()
    {
        res = 0, prd = 1;
    }

    // Add condition: res % p == r
    void add(T p, T r)
    {
        res += mul(r - res % p + p, euclid(prd, p).first + p, p) * prd;
        prd *= p;
        if (res >= prd)
            res -= prd;
    }

private:
    T prd;
    T mul(T a, T b, T p)
    {
        a %= p, b %= p;
        T q = (T)((long double)a * b / p);
        T r = a * b - q * p;
        while (r < 0)
            r += p;
        while (r >= p)
            r -= p;
        return r;
    }
    pair<T, T> euclid(T a, T b)
    {
        if (!b)
            return make_pair(1, 0);
        pair<T, T> r = euclid(b, a % b);
        return make_pair(r.second, r.first - a / b * r.second);
    }
};

const int64_t MOD0 = (1 << 21) * 476 + 1;
const int64_t MOD1 = (1 << 22) * 483 + 1;

NTT<MOD0, 1 << 22> NTTA;
NTT<MOD1, 1 << 22> NTTB;

int main(void)
{
    int64_t N, M;
    cin >> N >> M; 
    N++, M++;
    vector<int64_t> a(N), b(M);
    for (int64_t i = 0; i < N; i++)
        cin >> a[i];
    for (int64_t i = 0; i < M; i++)
        cin >> b[i];
    auto reta = NTTA.multiply(a, b);
    auto retb = NTTB.multiply(a, b);
    int64_t ret = 0;
    for (int64_t i = 0; i < N + M - 1; i++)
    {
        CRT<int64_t> crt;
       // cout << reta[i] << " " << retb[i] << '\n';
        crt.add(MOD0, reta[i]);
        crt.add(MOD1, retb[i]);
        ret = ret xor crt.res;
    }
    cout << ret << '\n'; 
    return 0;
}