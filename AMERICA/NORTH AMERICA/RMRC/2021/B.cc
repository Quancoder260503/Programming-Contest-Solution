#include "bits/stdc++.h"
using namespace std;
#define double long double
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

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point
{
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const
    {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream &operator<<(ostream &os, P p)
    {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
template <class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }
/* 
template <class P>
int sideOf(const P &s, const P &e, const P &p)
{
    auto a = (e - s).cross(p - s);
    double l = (e - s).dist();
    return (a > l) - (a < -l);
}
*/ 
typedef Point<Fraction> P;
Fraction rat(P a, P b) { return sgn(b.x) ? a.x / b.x : a.y / b.y; }
Fraction polyUnion(vector<vector<P>> &poly)
{
    Fraction ret = 0;
    for(int i = 0; i < poly.size(); i++) for(int v = 0; v < poly[i].size(); v++)
    {
        P A = poly[i][v], B = poly[i][(v + 1) % poly[i].size()];
        vector<pair<Fraction, int>> segs = {{0, 0}, {1, 0}};
        for(int j = 0; j < poly.size(); j++) if (i != j)
        {
            for(int u = 0; u < poly[j].size(); u++)
            {
                P C = poly[j][u], D = poly[j][(u + 1) % poly[j].size()];
                int sc = sideOf(A, B, C), sd = sideOf(A, B, D);
                //cout << sc << " " << sd << " " << A << " " << B << " " << C << " " << D << " " << A.cross(B) << '\n'; 
                if (sc != sd)
                {
                    Fraction sa = C.cross(D, A), sb = C.cross(D, B);
                    if (min(sc, sd) < 0) segs.emplace_back(sa / (sa - sb), sgn(sc - sd));
                }
                else if (!sc && !sd && j < i && sgn((B - A).dot(D - C)) > 0)
                {
                    segs.emplace_back(rat(C - A, B - A), 1);
                    segs.emplace_back(rat(D - A, B - A), -1);
                }
            }
        }
        sort(segs.begin(), segs.end());
        for (auto &s : segs) s.first = min(max(s.first, Fraction(0)), Fraction(1, 1));
        Fraction sum = 0;
        int ctr = segs[0].second;
        for(int j = 1; j < segs.size(); j++)
        {
            if (!ctr) sum += segs[j].first - segs[j - 1].first;
            ctr += segs[j].second;
        }
        ret += A.cross(B) * sum;
    }
    return ret / 2;
}
Fraction Area(vector<P>&pset)
{
    static int N = pset.size(); 
    Fraction ret = 0;
    for(int i = 0; i < N; i++) 
    {
        ret += pset[i].cross(pset[(i + 1) % N]); 
    }
    return ret / 2; 
}
int main(void)
{
    int N, Q; 
    while(cin >> N >> Q)
    {
        vector<P>pset;
        for(int i = 0; i < N; i++) 
        {
            P a;
            cin >> a.y >> a.x; 
            a.x =  a.x + Fraction(1, 2);
            a.y = -a.y - Fraction(1, 2);
            pset.push_back(a); 
        }
        auto area = Area(pset); 
        for(int i = 0; i < Q; i++)
        {
            P a; 
            cin >> a.y >> a.x; 
            a.x = a.x + Fraction(1, 2); 
            a.y = -a.y - Fraction(1, 2); 
            vector<P>pset2;
            pset2.push_back(P(a.x + Fraction(1, 2), a.y + Fraction(1, 2)));
            pset2.push_back(P(a.x - Fraction(1, 2), a.y + Fraction(1, 2)));
            pset2.push_back(P(a.x - Fraction(1, 2), a.y - Fraction(1, 2)));
            pset2.push_back(P(a.x + Fraction(1, 2), a.y - Fraction(1, 2)));
            vector<vector<P>>qset = {pset, pset2}; 
            auto ret = polyUnion(qset); 
            if(area == ret)
            {
                cout << Fraction(1, 1) << '\n'; 
            }
            else 
            {
                auto outside = ret - area; 
                cout << (Fraction(1, 1) - outside) << '\n'; 
            }
        }
    }
    return 0; 
}