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
vector<long long> mul(vector<int> &a, vector<int> &b)
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

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s; 
    cin >> s; 
    int n = s.size(); 
    vector<int>a(n + 1), b(n + 1);
    int acc = 0; 
    a[acc]++;
    b[n - acc]++;   
    int64_t cc = 0; 
    for(int i = 0; i < n; i++) { 
        acc += (s[i] == '1'); 
        cc += a[acc]; 
        a[acc]++; 
        b[n - acc]++; 
    }
    auto ret = mul(a, b);
    cout << cc << ' ';  
    for(int i = n + 1; i <= 2 * n; i++) { 
        cout << ret[i] << ' '; 
    }
    return 0;
}