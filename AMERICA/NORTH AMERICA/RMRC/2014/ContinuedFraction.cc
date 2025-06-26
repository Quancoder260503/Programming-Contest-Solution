#include "bits/stdc++.h"

using namespace std; 

typedef long long int dataType;
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

    num = num * b + x.num * a;
    denom *= b;

    reduce();

    return (*this);
}
Fraction &Fraction::operator-=(const Fraction &x)
{
    dataType g = gcd(denom, x.denom);
    dataType a = denom / g;
    dataType b = x.denom / g;

    num = num * b - x.num * a;
    denom *= b;

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
    return (num * x.denom) < (x.num * denom);
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
    cout.tie(0);  
    int n, m; 
    cin >> n >> m; 
    Fraction r1 = Fraction(0, 1); 
    Fraction r2 = Fraction(0, 1); 
    vector<int>a(n), b(m); 
    for(int i = 0; i < n; i++) {
        cin >> a[i]; 
    } 
    for(int i = 0; i < m; i++) { 
        cin >> b[i]; 
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for(int i = 0; i + 1 < a.size(); i++) {
        r1 = Fraction(r1.denom, a[i] * r1.denom + r1.num);  
    }
    r1 = r1 + Fraction(a.back(), 1); 
    for(int i = 0; i + 1 < b.size(); i++) { 
        r2 = Fraction(r2.denom, b[i] * r2.denom + r2.num); 
    }
    r2 = r2 + Fraction(b.back(), 1); 
    Fraction r = r1 + r2; 
    for(;;) { 
        cout << r.num / r.denom << ' '; 
        if(r.denom == 1) break; 
        r.num = r.num % r.denom; 
        swap(r.num, r.denom); 
    }
    cout << '\n'; 
    r = r1 - r2; 
    for(;;) { 
        cout << r.num / r.denom << ' '; 
        if(r.denom == 1) break; 
        r.num = r.num % r.denom; 
        swap(r.num, r.denom); 
    }
    cout << '\n'; 
    r = r1 * r2; 
    for(;;) { 
        cout << r.num / r.denom << ' '; 
        if(r.denom == 1) break; 
        r.num = r.num % r.denom; 
        swap(r.num, r.denom); 
    }
    cout << '\n'; 
    r = r1 / r2; 
    for(;;) { 
        cout << r.num / r.denom << ' '; 
        if(r.denom == 1) break; 
        r.num = r.num % r.denom; 
        swap(r.num, r.denom); 
    }
    cout << '\n'; 
    return 0; 
}