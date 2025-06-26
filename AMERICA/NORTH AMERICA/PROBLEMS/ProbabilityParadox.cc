#include "bits/stdc++.h"
using namespace std;
#define double long double
struct fraction
{
    int64_t num, den;
    fraction() : num(0), den(1){};
    fraction(int64_t _num, int64_t _den) : num(_num), den(_den){};
    fraction get_frac(int64_t n, int64_t d)
    {
        int64_t common = gcd(n, d);
        fraction ret;
        ret.num = n / common;
        ret.den = d / common;
        if (ret.den < 0)
        {
            ret.num = -ret.num;
            ret.den = -ret.den;
        }
        return ret;
    }
    fraction operator+(fraction &other)
    {
        int64_t n = this->num * other.den + other.num * this->den;
        int64_t d = this->den * other.den;
        return get_frac(n, d);
    }
    fraction operator-(fraction other)
    {
        int64_t n = this->num * other.den - other.num * this->den;
        int64_t d = this->den * other.den;
        return get_frac(n, d);
    }
    fraction operator*(fraction other)
    {
        int64_t n = this->num * other.num;
        int64_t d = this->den * other.den;
        return get_frac(n, d);
    }
    fraction operator/(fraction other)
    {
        int64_t n = this->num * other.den;
        int64_t d = this->den * other.num;
        return get_frac(n, d);
    }
    string to_str()
    {
        return to_string(num) + "/" + to_string(den);
    }
    static int64_t gcd(int64_t a, int64_t b)
    {
        if (a == 0)
            return b;
        if (b == 0)
            return a;
        if (a < 0 || b < 0)
            return gcd(abs(a), abs(b));
        return gcd(b, a % b);
    }
    int compareTo(fraction &other)
    {
        if (this->num * other.den == this->den * other.num)
            return 0;
        if (this->den * other.den > 0)
            return (this->num * other.den > this->den * other.num) ? 1 : -1;
        else
            return (this->num * other.den < this->den * other.num) ? 1 : -1;
    }
};
struct matrix
{
    vector<vector<fraction>> arr;
    void init(int N, int M)
    {
        vector<fraction> zeros(M, fraction(0, 1));
        for (int i = 0; i < N; i++)
        {
            arr.push_back(zeros);
        }
    }
    void gauss(int L)
    {
        for (int i = 0; i < L; i++)
        {
            for (int j = i + 1; j < L; j++)
            {
                fraction ratio = arr[j][i] / arr[i][i];
                for (int k = 0; k < L + 1; k++)
                {
                    arr[j][k] = arr[j][k] - ratio * arr[i][k];
                }
            }
        }
        arr[L - 1][L - 1] = arr[L - 1][L] / arr[L - 1][L];
        for (int i = L - 2; i >= 0; i--)
        {
            for (int j = i + 1; j < L; j++)
            {
                arr[i][L] = arr[i][L] - arr[j][L] * arr[i][j];
            }
            arr[i][L] = arr[i][L] / arr[i][i];
        }
    }
    void print()
    {
        for (int i = 0; i < arr.size(); i++)
        {
            for (int j = 0; j < arr[i].size(); j++)
            {
                cout << arr[i][j].to_str() << " ";
            }
            cout << '\n';
        }
    }
};
int ends_with(string A, string B)
{
    int N = A.length();
    for (int i = 0; i < N; i++)
    {
        string curr;
        for (int j = i; j < N; j++)
            curr += A[j];
        if (curr == B)
            return 1;
    }
    return 0;
}
signed main(void)
{
    string A, B;
    while (cin >> A >> B)
    {
        if (A == "$")
            break;
        int N = A.length();
        vector<string> S;
        for (int i = 0; i < N; i++)
        {
            S.push_back(A.substr(0, i));
            S.push_back(B.substr(0, i));
        }
        sort(S.begin(), S.end());
        S.erase(unique(S.begin(), S.end()), S.end());
        S.push_back(B);
        S.push_back(A);
        N = S.size();
        matrix ret;
        ret.init(N, N + 1);
        for (int i = 0; i < N; i++)
            ret.arr[i][i] = fraction(1, 1);
        int at = 0;
        for (int i = 0; i < N - 2; i++)
        {
            for (auto k : {'T', 'H'})
            {
                string S2 = S[i] + k;
                string suffix = "";
                int at = 0;
                for (int j = 0; j < N; j++)
                {
                    if (ends_with(S2, S[j]) && suffix.length() < S[j].length())
                    {
                        at = j;
                        suffix = S[j];
                    }
                }
                ret.arr[i][at] = ret.arr[i][at] - fraction(1, 2);
            }
        }
        ret.arr[N - 1][N] = fraction(1, 1);
        ret.gauss(N);
        cout << ret.arr[0][N].to_str() << '\n';
    }
    return 0;
}