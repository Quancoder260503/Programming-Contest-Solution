#include "bits/stdc++.h"
using namespace std;
#define MAXN 100005
#define lint long long
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
vector<lint> MULTIPLY(vector<lint> &a, vector<lint> &b)
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
lint acc[MAXN];
signed main(void)
{
    int n, m, q;
    lint  W;
    cin >> n >> q >> m >> W;
    memset(acc, 0, sizeof(acc));
    vector<vector<lint>> a(m, vector<lint>(n, 0));
    vector<vector<lint>> b(m, vector<lint>(q, 0));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            cin >> b[i][j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        reverse(b[i].begin(), b[i].end()); 
        auto res = MULTIPLY(a[i], b[i]);
        for (int j = 0; j < n; j++)
        { 
            acc[j] += res[q + j - 1];
        }
    }
    int ans = 0;
    for(int i = 0; i < n - q + 1; i++)
    {
        ans += (acc[i] > 1LL * W);
    }
    cout << ans << '\n';
    return 0;
}