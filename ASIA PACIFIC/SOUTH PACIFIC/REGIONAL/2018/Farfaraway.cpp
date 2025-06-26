#include "bits/stdc++.h"
using namespace std;
const int MAXN = 101;
#define lint long long
const lint INF = 1e17;
using type = lint;
struct Matrix
{
    vector<vector<type>> data;
    int row() const { return data.size(); }
    int col() const { return data[0].size(); }
    auto &operator[](int i) { return data[i]; }
    const auto &operator[](int i) const { return data[i]; }
    Matrix() = default;

    Matrix(int r, int c) : data(r, vector<type>(c)) {}

    Matrix(const vector<vector<type>> &d) : data(d)
    {
        assert(d.size());
        int size = d[0].size();
        assert(size);
        for (auto x : d)
            assert(x.size() == size);
    }
    friend ostream &operator<<(ostream &out, const Matrix &d)
    {
        for (auto x : d.data)
        {
            for (auto y : x)
                out << y << ' ';
            out << '\n';
        }
        return out;
    }
    static Matrix identity(long long n)
    {
        Matrix a = Matrix(n, n);
        while (n--)
            a[n][n] = 1;
        return a;
    }
    static Matrix infinity(long long n)
    {
        Matrix a = Matrix(n, n);
        for (int i = 0; i < a.row(); i++)
        {
            for (int j = 0; j < a.col(); j++)
            {
                a[i][j] = INF;
            }
        }
        return a;
    }
    Matrix operator*(const Matrix &b)
    {
        Matrix a = *this;
        assert(a.col() == b.row());

        Matrix c(a.row(), b.col());
        for (int i = 0; i < a.row(); ++i)
        {
            for (int j = 0; j < b.col(); ++j)
            {
                c[i][j] = INF;
                for (int k = 0; k < a.col(); ++k)
                {
                    if (a[i][k] >= INF or b[k][j] >= INF)
                        continue;
                    c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
                }
            }
        }
        return c;
    }
    Matrix pow(long long exp)
    {
        assert(row() == col());
        Matrix base = *this, ans = *this;
        for (; exp > 0; exp >>= 1, base = base * base)
            if (exp & 1)
                ans = ans * base;
        return ans;
    }
};
int n, m;
Matrix adj(MAXN, MAXN);
Matrix pw[MAXN];
bool f(lint x)
{
    if (x == -1) return 0;
    Matrix leg(2, MAXN);
    for (int i = 0; i < MAXN; i++)
    {
        leg[0][i] = adj[0][i]; 
        leg[1][i] = adj[1][i]; 
    }
    for (int i = 0; i < 35; i++)
    {
        if ((1LL << i) & x)
        {
            leg = leg * pw[i];
        }
    }
    lint ans = INF;
    for (int i = 1; i <= n; i++)
    {
        ans = min(ans, leg[1][i]);
    }
    return (ans <= 1LL * m);
}
signed main(void)
{
    cin >> n >> m;
    for (int i = 0; i < MAXN; i++)
    {
        for (int j = 0; j < MAXN; j++)
        {
            adj[i][j] = INF;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> adj[i][j];
        }
    }
    pw[0] = adj;
    for (int i = 1; i < 35; i++)
    {
        pw[i] = pw[i - 1] * pw[i - 1];
    }
    lint lo = -1;
    lint hi = (lint)1e9;
    while (lo < hi)
    {
        lint mid = (hi + lo + 1) / 2;
        if (f(mid))
        {
            lo = mid;
        }
        else
        {
            hi = mid - 1;
        }
    }
    cout << lo + 1 << '\n';
    return 0;
}