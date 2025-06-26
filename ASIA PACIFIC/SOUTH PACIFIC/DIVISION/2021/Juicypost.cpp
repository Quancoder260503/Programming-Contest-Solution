#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)101;
#define lint long long
int n;
lint m;
const int mod = 1e9 + 7;
string s[MAXN];
lint dp[MAXN][MAXN];
vector<string> arr;
set<string> ss;
int N;
bool match(const string &text, const string &pattern)
{
    if (text.size() < pattern.size())
        return 0;
    int N = text.size() - pattern.size();
    for (int i = text.size() - 1; i >= N; i--)
    {
        if (text[i] != pattern[i - N])
            return 0;
    }
    return 1;
}
struct matrix
{
    lint arr[MAXN][MAXN];
    void init()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                arr[i][j] = 0;
            }
        }
        return;
    }
};
matrix operator*(const matrix &a, const matrix &b)
{
    matrix c;
    c.init();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                c.arr[i][j] = (c.arr[i][j] + 1LL * a.arr[i][k] % mod * b.arr[k][j] % mod + mod) % mod;
            }
        }
    }
    return c;
}
bool check(string &s)
{
    int N = s.length();
    for (int i = 0; i < N; i++)
    {
        for (int j = i; j < N; j++)
        {
            if (ss.count(s.substr(i, j + 1)))
                return 0;
        }
    }
    return 1;
}
bool good[MAXN];
signed main(void)
{
    cin >> n >> m;
    arr.push_back("");
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        for (int j = 0; j < s[i].length(); j++)
        {
            arr.push_back(s[i].substr(0, j + 1));
        }
        ss.insert(s[i]);
    }
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    N = arr.size();
    for (int i = 0; i < N; i++)
    {
        good[i] = check(arr[i]);
    }
    for (int i = 0; i < N; i++)
    {
        if (!good[i])
            continue;
        for (int j = 0; j < N; j++)
        {
            if (!good[j]) continue;
            for (int x = 0; x < 26; x++)
            {
                string now = arr[i] + (char)('a' + x);
                string suff = arr[j];
                bool bad = 0;
                for (int k = now.length() - 1; k >= 0; k--)
                {
                    bad = bad || (ss.count(now.substr(k, now.length())));
                }
                if (!match(now, suff))
                    continue;
                for (int k = 0; k < N; k++)
                {
                    if (match(now, arr[k]))
                    {
                        if (suff.length() < arr[k].length())
                        {
                            suff = arr[k];
                        }
                    }
                }
                if (suff == arr[j])
                {
                    dp[i][j]++;
                }
            }
        }
    }
    matrix coef;
    coef.init();
    matrix res;
    res.init();
    for (int i = 0; i < N; i++)
    {
        res.arr[i][i] = 1;
        for (int j = 0; j < N; j++)
        {
            coef.arr[i][j] = dp[i][j];
        }
    }
    while (m)
    {
        if (m & 1)
            res = res * coef;
        coef = coef * coef;
        m = m / 2;
    }
    lint ans = 0;
    for (int i = 0; i < N; i++)
    {
        ans = (ans + res.arr[0][i] + mod) % mod;
    }
    cout << ans << endl;
    return 0;
}