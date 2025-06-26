#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)1e6 + 10
#define M 50000
using cd = complex<double>;
const double PI = acos(-1);
int n, k, m;
string a, b;
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
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin >> a >> b;
    if (a[0] == '0' || b[0] == '0')
    {
        puts("0");
        return 0;
    }
    vector<cd> A, B;
    for (int i = a.length() - 1; i >= 0; i--)
    {
        A.push_back(cd(a[i] - '0', 0));
    }
    for (int i = b.length() - 1; i >= 0; i--)
    {
        B.push_back(cd(b[i] - '0', 0));
    }
    int sz = 1;
    while (sz < A.size() + B.size())
    {
        sz = sz * 2;
    }
    A.resize(sz);
    B.resize(sz);
    fft(A, (int)A.size(), false);
    fft(B, (int)B.size(), false);
    for (int i = 0; i < sz; i++)
    {
        A[i] *= B[i];
    }
    fft(A, (int)A.size(), true);
    vector<long long> res(sz);
    for (int i = 0; i < sz; i++)
    {
        res[i] = 1LL * round(A[i].real());
    }
    vector<int> digit(res.size());
    int carry = 0;
    for (int i = 0; i < (int)res.size(); i++)
    {
        digit[i] = (res[i] + carry) % 10;
        carry = (res[i] + carry) / 10;
    }
    int cnt = (int)res.size();
    for (int i = cnt - 1; i >= 0; i--)
    {
        if (digit[i])
        {
            cnt = i + 1;
            break;
        }
    }
    for (int i = cnt - 1; i >= 0; i--)
    {
        cout << digit[i];
    }
    cout << '\n';
    return 0;
}