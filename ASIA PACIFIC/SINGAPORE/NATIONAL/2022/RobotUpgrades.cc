#include "bits/stdc++.h"

using namespace std;

const int64_t mod = 998244353; 

int64_t fpow(int64_t a, int64_t k)
{
    if (!k) return 1;
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
        for (int64_t i = 1; i <= maxf; i <<= 1)
        {
            iv[i] = fpow(i, mod - 2);
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
    int64_t iv[maxf + 1];
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
            int64_t in = iv[n];
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

NTT<mod, 1 << 20>ntt; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int64_t n, m; 
    cin >> n >> m; 
    vector<int64_t>a(m);
    for(int i = 0; i < m; i++) { 
        cin >> a[i]; 
    }
    vector<int64_t>fact(n + 1), ifact(n + 1); 
    fact[0] = ifact[0] = 1; 
    for(int i = 1; i < n + 1; i++) { 
        fact[i] = i * fact[i - 1] % mod; 
        ifact[i] = fpow(i, mod - 2) * ifact[i - 1] % mod; 
    }
    m--; 
    vector<int64_t>ret(a[m] + 1, 1), c(n + 1);
    for (int i = 0; i <= n; i++) c[i] = ifact[i];
    for(int j = m; j > 0; j--) { 
        for(int i = 0; i < ret.size(); i++) ret[i] = ret[i] % mod * ifact[i] % mod; 
        ret = ntt.multiply(ret, c); 
        ret.resize(a[j - 1] + 1);
        for(int i = 0; i < ret.size(); i++) ret[i] = ret[i] % mod * fact[i] % mod; 
        cout << '\n'; 
    }
    int64_t res = 0; 
    for(int i = 0; i <= a[0]; i++) { 
        res = (res + fact[n] % mod * ifact[i] % mod * ifact[n - i] % mod * ret[i] % mod) % mod; 
    }
    cout << res << '\n'; 
    return 0;
}