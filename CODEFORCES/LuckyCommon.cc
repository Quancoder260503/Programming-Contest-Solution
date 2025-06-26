#include "bits/stdc++.h"

using namespace std;

vector<int> prefix_function(const string &s)
{
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

template <int D, typename T>
struct Vec : public vector<Vec<D - 1, T>>
{
    static_assert(D >= 1, "Dimension must be positive");
    template <typename... Args>
    Vec(int n = 0, Args... args) : vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...)) {}
};
template <typename T>
struct Vec<1, T> : public vector<T>
{
    Vec(int n = 0, T val = T()) : vector<T>(n, val) {}
};

int main(void)
{
    string a, b, c; 
    cin >> a >> b >> c; 
    auto get_s = [&](string &a, string b)
    {
        if(a.length() < b.length()) a = b; 
        return; 
    };
    a = " " + a; 
    b = " " + b;
    vector<int>pi = prefix_function(c);
    int na = a.length(), nb = b.length(), nc = c.length();
    Vec<3, string>dyn(na, nb, nc + 1);
    for(int i = 1; i < na; i++) for(int j = 1; j < nb; j++) for(int k = 0; k < nc; k++)
    {
        if(a[i] == b[j])
        {
            char ch = a[i]; int p = k;
            while(p > 0 && ch != c[p]) p = pi[p - 1];
            if(ch == c[p]) ++p;
            get_s(dyn[i][j][p], dyn[i - 1][j - 1][k] + ch);
        }
        get_s(dyn[i][j][k], dyn[i][j - 1][k]);
        get_s(dyn[i][j][k], dyn[i - 1][j][k]);
    }
    string ret;
    for(int i = 0; i < nc; i++) get_s(ret, dyn[na - 1][nb - 1][i]);
    if(ret == "") cout << 0 << '\n'; 
    else cout << ret.c_str() << '\n';
    return 0; 
}