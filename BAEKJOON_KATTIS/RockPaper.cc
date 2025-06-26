#include "bits/stdc++.h"

using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

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
vector<int64_t> mul(vector<int> &a, vector<int> &b)
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
    vector<int64_t> res(n);
    for (int i = 0; i < n; i++)
    {
        res[i] = 1LL * round(A[i].real());
    }
    return res;
}

int main(void)
{
    int N, M; 
    string A, B; 
    while(cin >> N >> M >> A >> B)
    {
        vector<int>ret(N + M - 1);
        reverse(B.begin(), B.end());
        auto doit = [&](char p, char q)
        {
            vector<int> a(N), b(M); 
            for (int i = 0; i < N; i++) if (A[i] == p) a[i]++;
            for (int i = 0; i < M; i++) if (B[i] == q) b[i]++;
            auto w = mul(a, b);
            for(int i = 0; i < N + M - 1; i++) ret[i] += w[i]; 
            return;
        };
        doit('S', 'R');
        doit('R', 'P'); 
        doit('P', 'S'); 
        int res = 0; 
        for(int i = M - 1; i < N + M - 1; i++) res = max(res, ret[i]); 
        cout << res << '\n'; 
    }
    return 0; 
}