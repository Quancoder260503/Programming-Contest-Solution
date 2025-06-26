#include "bits/stdc++.h"
using namespace std;
#define Lint long long
struct FFT
{
    using cd = complex<double>;
    const double PI = acos(-1);
    int n, k, m;
    void fft(vector<cd> &a, int sz, bool invert)
    {
        for (int i = 1, mask = 0; i < sz; i++)
        {
            int bit = sz >> 1;
            for (; mask & bit; bit = bit / 2)
            {
                mask = mask xor bit;
            }
            mask = mask xor bit;
            if (i < mask)
            {
                swap(a[i], a[mask]);
            }
        }
        for (int len = 2; len <= sz; len = len * 2)
        {
            double angle = 2 * PI / len * (invert ? -1 : 1);
            cd wang(cos(angle), sin(angle));
            for (int i = 0; i < sz; i += len)
            {
                cd w(1);
                for (int j = 0; j < len / 2; j++)
                {
                    cd u = a[i + j];
                    cd v = w * a[i + j + len / 2];
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w = w * wang;
                }
            }
        }
        if (invert)
        {
            for (int i = 0; i < sz; i++)
            {
                a[i] /= sz;
            }
        }
        return;
    }
    vector<Lint> mul(vector<Lint> &a, vector<Lint> &b)
    {
        vector<cd> A(a.begin(), a.end()), B(b.begin(), b.end());
        int n = 1;
        while (n < A.size() + B.size())
        {
            n = n * 2;
        }
        A.resize(n);
        B.resize(n);
        fft(A, (int)A.size(), false);
        fft(B, (int)B.size(), false);
        for (int i = 0; i < n; i++)
        {
            A[i] *= B[i];
        }
        fft(A, (int)A.size(), true);
        vector<long long> res(n);
        for (int i = 0; i < n; i++)
        {
            res[i] = 1LL * round(A[i].real());
        }
        return res;
    }
};
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<Lint>a(N);
        vector<Lint>b(N); 
        for(int i = 1; i < N; i++)
        {
            a[1LL * i % N * i % N]++; 
            b[2LL * i % N * i % N]++;
        }
        FFT poly;
        auto ans = poly.mul(a, a);  
        Lint ret = 0; 
        for(int i = 1; i < N; i++)
        {
            Lint cur = 1LL * i % N * i % N;
            ret += (ans[cur] + ans[cur + N] - b[cur]) / 2 + b[cur]; 
        }
        cout << ret << '\n'; 
    }
    return 0;
}