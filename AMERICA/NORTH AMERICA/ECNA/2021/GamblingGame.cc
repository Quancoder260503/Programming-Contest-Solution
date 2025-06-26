#include "bits/stdc++.h"

using namespace std; 

typedef long long dataType;
class Fraction
{
public:
    Fraction(dataType num = 0, dataType denom = 1);

    double toDouble() const;

    void reduce();

    // Changes the Fraction itself.
    void selfReciprocal();

    // Returns a new Fraction, leaving the original.
    Fraction reciprocal() const;

    Fraction &operator+=(const Fraction &x);
    Fraction &operator-=(const Fraction &x);
    Fraction &operator*=(const Fraction &x);
    Fraction &operator/=(const Fraction &x);
    Fraction &operator-();

    bool operator<(const Fraction &x) const;
    bool operator==(const Fraction &x) const;

    dataType num, denom;
};

Fraction operator+(const Fraction &x, const Fraction &y);
Fraction operator-(const Fraction &x, const Fraction &y);
Fraction operator*(const Fraction &x, const Fraction &y);
Fraction operator/(const Fraction &x, const Fraction &y);

istream &operator>>(istream &is, Fraction &x);
ostream &operator<<(ostream &os, const Fraction &x);

Fraction::Fraction(dataType n, dataType d)
{
    if (d < 0)
    {
        num = -n;
        denom = -d;
    }
    else
    {
        num = n;
        denom = d;
    }
    reduce();
}

double Fraction::toDouble() const
{
    return 1.0 * num / denom;
}

// Howard's GCD function with no checks
dataType gcd(dataType a, dataType b)
{
    dataType r;
    while (b)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

void Fraction::reduce()
{
    dataType g = gcd(abs(num), denom);
    num /= g;
    denom /= g;
}

void Fraction::selfReciprocal()
{
    swap(num, denom);
    if (denom < 0)
    {
        num = -num;
        denom = -denom;
    }
}

Fraction Fraction::reciprocal() const
{
    return Fraction(denom, num);
}
Fraction &Fraction::operator+=(const Fraction &x)
{
    dataType g = gcd(denom, x.denom);

    dataType a = denom / g;
    dataType b = x.denom / g;

    num = 1LL * num * b + 1LL * x.num * a;
    denom = 1LL * denom * b;

    reduce();

    return (*this);
}
Fraction &Fraction::operator-=(const Fraction &x)
{
    dataType g = gcd(denom, x.denom);
    dataType a = denom / g;
    dataType b = x.denom / g;

    num = 1LL * num * b - 1LL * x.num * a;
    denom = 1LL * denom * b;

    reduce();
    return (*this);
}

Fraction &Fraction::operator*=(const Fraction &x)
{
    num *= x.num;
    denom *= x.denom;
    reduce();
    return (*this);
}

Fraction &Fraction::operator/=(const Fraction &x)
{
    num *= x.denom;
    denom *= x.num;

    if (denom < 0)
    {
        num = -num;
        denom = -denom;
    }
    reduce();
    return (*this);
}

Fraction &Fraction::operator-()
{
    num *= -1;
    return *this;
}

// Careful with overflow. If it is an issue, you can compare the
// double values, but you SHOULD check for equality BEFORE converting
bool Fraction::operator<(const Fraction &x) const
{
    return (1LL * num * x.denom) < (1LL * x.num * denom);
}

bool Fraction::operator==(const Fraction &x) const
{
    return (num == x.num) && (denom == x.denom);
}

bool operator>(const Fraction &x, const Fraction &y)
{
    return !(x == y) && !(x < y);
}

bool operator<=(const Fraction &x, const Fraction &y)
{
    return (x == y) || (x < y);
}

bool operator>=(const Fraction &x, const Fraction &y)
{
    return (x == y) || (x > y);
}

bool operator!=(const Fraction &x, const Fraction &y)
{
    return !(x == y);
}

Fraction operator+(const Fraction &x, const Fraction &y)
{
    Fraction a(x);
    a += y;
    return a;
}

Fraction operator-(const Fraction &x, const Fraction &y)
{
    Fraction a(x);
    a -= y;
    return a;
}

Fraction operator*(const Fraction &x, const Fraction &y)
{
    Fraction a(x);
    a *= y;
    return a;
}

Fraction operator/(const Fraction &x, const Fraction &y)
{
    Fraction a(x);
    a /= y;
    return a;
}
istream &operator>>(istream &is, Fraction &x)
{
    is >> x.num;

    char ch;
    is >> ch;
    if (ch != '/')
    {
        is.putback(ch);
        x.denom = 1;
    }
    else
    {
        is >> x.denom;
        if (x.denom < 0)
        {
            x.num = -x.num;
            x.denom = -x.denom;
        }
        x.reduce();
    }

    return is;
}
ostream &operator<<(ostream &os, const Fraction &x)
{
    os << x.num;
    os << '/' << x.denom;
    return os;
}

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    int n, m, p; 
    cin >> m >> n >> p; 
    vector<vector<Fraction>>dyn(n + 1, vector<Fraction>(p + 1, Fraction(-1, 1)));
    vector<Fraction>ways(m + 1);
    ways[0] = Fraction(1, 1);
    for(int i = 1; i <= p; i++) {
        ways[i] = ways[i - 1] * Fraction(m - i + 1 - 2 * n, m - i + 1); 
    }
    function<Fraction(int, int)> func = [&](int x, int y) {
        if(x == 0) return (y >= 0 ? ways[y] : Fraction(0, 1)); 
        if(y == 0) return Fraction((x == 0), 1); 
        if(dyn[x][y] != Fraction(-1, 1)) return dyn[x][y]; 
        Fraction &ret = dyn[x][y]; 
        ret = func(x - 1, y - 1) * Fraction(2 * (n - x + 1), m - y + 1) + func(x, y - 1) * Fraction((m - y + 1 - 2 * (n - x)), m - y + 1); 
        return ret; 
    }; 
    cout << func(n, p) - func(n, p - 1) << '\n'; 
    return 0; 
}
/* dyn[x][y] = {probability that we have covered x squares after y rounds}
   dyn[x][y] = dyn[x - 1][y - 1] * 2 * (n - x + 1) / (m - y + 1) + dyn[x][y - 1] * (1 - 2 * (n - x) / (m - y + 1))
*/ 