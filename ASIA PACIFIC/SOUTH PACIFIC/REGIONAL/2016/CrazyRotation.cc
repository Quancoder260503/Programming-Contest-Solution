#include "bits/stdc++.h"

using namespace std;

using cd = complex<double>;
const double PI = acos(-1);
const int maxf = 1e6 + 2; 

vector<int>g[maxf]; 

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
    string S;
    while (cin >> N >> M >> S)
    {
        vector<int> ret(N);
        auto doit = [&](char q)
        {
            vector<int> a(N);
            vector<int> b(N);
            for (int i = 0; i < N; i++) a[i] = (S[i] == q);
            for (int i = 0; i < N; i++) b[N - i - 1] = (S[i] == q);
            auto poly = mul(a, b);
            for (int i = 0; i < poly.size(); i++) ret[(i + 1) % N] += poly[i];
            return;
        };
        for (auto p : {'R', 'Y', 'B'}) doit(p);
        for(int i = 0; i < N; i++) ret[i] = N - ret[i]; 
        vector<int> ord(N);
        iota(ord.begin(), ord.end(), 0);
        auto cmp = [&](int a, int b)
        {
            return ret[a] < ret[b];
        };
        sort(ord.begin(), ord.end(), cmp);
        for(auto v : ord) g[ret[v]].push_back(v); 
        for(int i = 0; i < maxf; i++) sort(g[i].begin(), g[i].end());
        M++;
        for(int i = 0; i < maxf; i++)
        {
            if(g[i].size() < M)
            {
                M = M - g[i].size(); 
            }
            else
            {
                cout << (g[i][0] == 0 ? g[i][1] : g[i][0]) << '\n'; 
                break; 
            }
        }
    }
    return 0;
}