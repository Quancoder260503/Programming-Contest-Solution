#include "bits/stdc++.h"
using namespace std;
#ifndef EPS // allow test files to overwrite EPS
#define EPS 1e-6
#define double long double
#endif
const double PI = acos(-1.0);
double DEG_to_RAD(double d) { return d * PI / 180.0; }
double RAD_to_DEG(double r) { return r * 180.0 / PI; }

inline int cmp(double a, double b)
{
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

// for int types
template <typename T, typename std::enable_if<!std::is_floating_point<T>::value>::type * = nullptr>
inline int cmp(T a, T b)
{
    return (a == b) ? 0 : (a < b) ? -1
                                  : 1;
}

template <typename T>
struct P
{
    T x, y;
    P() { x = y = T(0); }
    P(T _x, T _y) : x(_x), y(_y) {}

    P operator+(const P &a) const { return P(x + a.x, y + a.y); }
    P operator-(const P &a) const { return P(x - a.x, y - a.y); }
    P operator*(T k) const { return P(x * k, y * k); }
    P<double> operator/(double k) const { return P(x / k, y / k); }

    T operator*(const P &a) const { return x * a.x + y * a.y; } // dot product
    T operator%(const P &a) const { return x * a.y - y * a.x; } // cross product

    int cmp(const P<T> &q) const
    {
        if (int t = ::cmp(x, q.x))
            return t;
        return ::cmp(y, q.y);
    }

#define Comp(x) \
    bool operator x(const P &q) const { return cmp(q) x 0; }
    Comp(>) Comp(<) Comp(==) Comp(>=) Comp(<=) Comp(!=)
#undef Comp

        T norm()
    {
        return x * x + y * y;
    }

    // Note: There are 2 ways for implementing len():
    // 1. sqrt(norm()) --> fast, but inaccurate (produce some values that are of order X^2)
    // 2. hypot(x, y) --> slow, but much more accurate
    double len() { return hypot(x, y); }

    P<double> rotate(double alpha)
    {
        double cosa = cos(alpha), sina = sin(alpha);
        return P(x * cosa - y * sina, x * sina + y * cosa);
    }
};
using Point = P<double>;
// Compare points by (y, x)
template <typename T = double>
bool cmpy(const P<T> &a, const P<T> &b)
{
    if (cmp(a.y, b.y))
        return a.y < b.y;
    return a.x < b.x;
};

template <typename T>
int ccw(P<T> a, P<T> b, P<T> c)
{
    return cmp((b - a) % (c - a), T(0));
}

int RE_TRAI = ccw(P<int>(0, 0), P<int>(0, 1), P<int>(-1, 1));
int RE_PHAI = ccw(P<int>(0, 0), P<int>(0, 1), P<int>(1, 1));

template <typename T>
istream &operator>>(istream &cin, P<T> &p)
{
    cin >> p.x >> p.y;
    return cin;
}
template <typename T>
ostream &operator<<(ostream &cout, const P<T> &p)
{
    cout << p.x << ' ' << p.y;
    return cout;
}

double angle(Point a, Point o, Point b)
{ // min of directed angle AOB & BOA
    a = a - o;
    b = b - o;
    return acos((a * b) / sqrt(a.norm()) / sqrt(b.norm()));
}

double directed_angle(Point a, Point o, Point b)
{ // angle AOB, in range [0, 2*PI)
    double t = -atan2(a.y - o.y, a.x - o.x) + atan2(b.y - o.y, b.x - o.x);
    while (t < 0)
        t += 2 * PI;
    return t;
}

// Distance from p to Line ab (closest Point --> c)
// i.e. c is projection of p on AB
double distToLine(Point p, Point a, Point b, Point &c)
{
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    c = a + (ab * u);
    return (p - c).len();
}

// Distance from p to segment ab (closest Point --> c)
double distToLineSegment(Point p, Point a, Point b, Point &c)
{
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    if (u < 0.0)
    {
        c = Point(a.x, a.y);
        return (p - a).len();
    }
    if (u > 1.0)
    {
        c = Point(b.x, b.y);
        return (p - b).len();
    }
    return distToLine(p, a, b, c);
}

// NOTE: WILL NOT WORK WHEN a = b = 0.
struct Line
{
    double a, b, c; // ax + by + c = 0
    Point A, B;     // Added for polygon intersect line. Do not rely on assumption that these are valid

    Line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}

    Line(Point _A, Point _B) : A(_A), B(_B)
    {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }
    Line(Point P, double m)
    {
        a = -m;
        b = 1;
        c = -((a * P.x) + (b * P.y));
    }
    double f(Point p)
    {
        return a * p.x + b * p.y + c;
    }
};
ostream &operator>>(ostream &cout, const Line &l)
{
    cout << l.a << "*x + " << l.b << "*y + " << l.c;
    return cout;
}

bool areParallel(Line l1, Line l2)
{
    return cmp(l1.a * l2.b, l1.b * l2.a) == 0;
}

bool areSame(Line l1, Line l2)
{
    return areParallel(l1, l2) && cmp(l1.c * l2.a, l2.c * l1.a) == 0 && cmp(l1.c * l2.b, l1.b * l2.c) == 0;
}

bool areIntersect(Line l1, Line l2, Point &p)
{
    if (areParallel(l1, l2))
        return false;
    double dx = l1.b * l2.c - l2.b * l1.c;
    double dy = l1.c * l2.a - l2.c * l1.a;
    double d = l1.a * l2.b - l2.a * l1.b;
    p = Point(dx / d, dy / d);
    return true;
}

// closest point from p in line l.
void closestPoint(Line l, Point p, Point &ans)
{
    if (fabs(l.b) < EPS)
    {
        ans.x = -(l.c) / l.a;
        ans.y = p.y;
        return;
    }
    if (fabs(l.a) < EPS)
    {
        ans.x = p.x;
        ans.y = -(l.c) / l.b;
        return;
    }
    Line perp(l.b, -l.a, -(l.b * p.x - l.a * p.y));
    areIntersect(l, perp, ans);
}

// Segment intersect
// Tested:
// - https://cses.fi/problemset/task/2190/
// returns true if p is on segment [a, b]
template <typename T>
bool onSegment(const P<T> &a, const P<T> &b, const P<T> &p)
{
    return ccw(a, b, p) == 0 && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

// Returns true if segment [a, b] and [c, d] intersects
// End point also returns true
template <typename T>
bool segmentIntersect(const P<T> &a, const P<T> &b, const P<T> &c, const P<T> &d)
{
    if (onSegment(a, b, c) || onSegment(a, b, d) || onSegment(c, d, a) || onSegment(c, d, b))
    {
        return true;
    }

    return ccw(a, b, c) * ccw(a, b, d) < 0 && ccw(c, d, a) * ccw(c, d, b) < 0;
}
template <typename T>
struct Matrix
{
    int n_row, n_col;
    vector<T> x;

    // accessors
    typename vector<T>::iterator operator[](int r)
    {
        return x.begin() + r * n_col;
    }
    inline T get(int i, int j) const { return x[i * n_col + j]; }
    vector<T> at(int r) const
    {
        return vector<T>{x.begin() + r * n_col, x.begin() + (r + 1) * n_col};
    }

    // constructors
    Matrix() = default;
    Matrix(int _n_row, int _n_col) : n_row(_n_row), n_col(_n_col), x(n_row * n_col) {}
    Matrix(const vector<vector<T>> &d) : n_row(d.size()), n_col(d.size() ? d[0].size() : 0)
    {
        for (auto &row : d)
            std::copy(row.begin(), row.end(), std::back_inserter(x));
    }

    // convert to 2d vec
    vector<vector<T>> vecvec() const
    {
        vector<vector<T>> ret(n_row);
        for (int i = 0; i < n_row; i++)
        {
            std::copy(x.begin() + i * n_col,
                      x.begin() + (i + 1) * n_col,
                      std::back_inserter(ret[i]));
        }
        return ret;
    }
    operator vector<vector<T>>() const { return vecvec(); }

    static Matrix identity(int n)
    {
        Matrix res(n, n);
        for (int i = 0; i < n; i++)
        {
            res[i][i] = 1;
        }
        return res;
    }

    Matrix transpose() const
    {
        Matrix res(n_col, n_row);
        for (int i = 0; i < n_row; i++)
        {
            for (int j = 0; j < n_col; j++)
            {
                res[j][i] = this->get(i, j);
            }
        }
        return res;
    }

    Matrix &operator*=(const Matrix &r) { return *this = *this * r; }
    Matrix operator*(const Matrix &r) const
    {
        assert(n_col == r.n_row);
        Matrix res(n_row, r.n_col);

        for (int i = 0; i < n_row; i++)
        {
            for (int k = 0; k < n_col; k++)
            {
                for (int j = 0; j < r.n_col; j++)
                {
                    res[i][j] += this->get(i, k) * r.get(k, j);
                }
            }
        }
        return res;
    }

    Matrix pow(long long n) const
    {
        assert(n_row == n_col);
        Matrix res = identity(n_row);
        if (n == 0)
            return res;

        bool res_is_id = true;
        for (int i = 63 - __builtin_clzll(n); i >= 0; i--)
        {
            if (!res_is_id)
                res *= res;
            if ((n >> i) & 1)
                res *= (*this), res_is_id = false;
        }
        return res;
    }

    // Gauss
    template <typename T2, typename std::enable_if<std::is_floating_point<T2>::value>::type * = nullptr>
    static int choose_pivot(const Matrix<T2> &mtr, int h, int c) noexcept
    {
        int piv = -1;
        for (int j = h; j < mtr.n_row; j++)
        {
            if (mtr.get(j, c) and (piv < 0 or std::abs(mtr.get(j, c)) > std::abs(mtr.get(piv, c))))
                piv = j;
        }
        return piv;
    }
    template <typename T2, typename std::enable_if<!std::is_floating_point<T2>::value>::type * = nullptr>
    static int choose_pivot(const Matrix<T2> &mtr, int h, int c) noexcept
    {
        for (int j = h; j < mtr.n_row; j++)
        {
            if (mtr.get(j, c) != T(0))
                return j;
        }
        return -1;
    }

    // return upper triangle matrix
    [[nodiscard]] Matrix gauss() const
    {
        int c = 0;
        Matrix mtr(*this);
        vector<int> ws;
        ws.reserve(n_col);
        for (int h = 0; h < n_row; h++)
        {
            if (c == n_col)
                break;
            int piv = choose_pivot(mtr, h, c);
            if (piv == -1)
            {
                c++;
                h--;
                continue;
            }
            if (h != piv)
            {
                for (int w = 0; w < n_col; w++)
                {
                    swap(mtr[piv][w], mtr[h][w]);
                    mtr[piv][w] *= -1; // for determinant
                }
            }
            ws.clear();
            for (int w = c; w < n_col; w++)
            {
                if (mtr[h][w] != 0)
                    ws.emplace_back(w);
            }
            const T hcinv = T(1) / mtr[h][c];
            for (int hh = 0; hh < n_row; hh++)
            {
                if (hh != h)
                {
                    const T coeff = mtr[hh][c] * hcinv;
                    for (auto w : ws)
                        mtr[hh][w] -= mtr[h][w] * coeff;
                    mtr[hh][c] = 0;
                }
            }
            c++;
        }
        return mtr;
    }

    // For upper triangle matrix
    T det() const
    {
        T ret = 1;
        for (int i = 0; i < n_row; i++)
        {
            ret *= get(i, i);
        }
        return ret;
    }

    // return rank of inverse matrix. If rank < n -> not invertible
    int inverse()
    {
        assert(n_row == n_col);
        vector<vector<T>> ret = identity(n_row), tmp = *this;
        int rank = 0;

        for (int i = 0; i < n_row; i++)
        {
            int ti = i;
            while (ti < n_row && tmp[ti][i] == 0)
                ++ti;
            if (ti == n_row)
                continue;
            else
                ++rank;

            ret[i].swap(ret[ti]);
            tmp[i].swap(tmp[ti]);

            T inv = T(1) / tmp[i][i];
            for (int j = 0; j < n_col; j++)
                ret[i][j] *= inv;
            for (int j = i + 1; j < n_col; j++)
                tmp[i][j] *= inv;

            for (int h = 0; h < n_row; h++)
            {
                if (i == h)
                    continue;
                const T c = -tmp[h][i];
                for (int j = 0; j < n_col; j++)
                    ret[h][j] += ret[i][j] * c;
                for (int j = i + 1; j < n_col; j++)
                    tmp[h][j] += tmp[i][j] * c;
            }
        }

        *this = ret;
        return rank;
    }

    // sum of all elements in this matrix
    T sum_all()
    {
        return submatrix_sum(0, 0, n_row, n_col);
    }

    // sum of [r1, r2) x [c1, c2)
    T submatrix_sum(int r1, int c1, int r2, int c2)
    {
        T res{0};
        for (int r = r1; r < r2; ++r)
        {
            res += std::accumulate(
                x.begin() + r * n_col + c1,
                x.begin() + r * n_col + c2,
                T{0});
        }
        return res;
    }
};
template <typename T>
ostream &operator<<(ostream &cout, const Matrix<T> &m)
{
    cout << m.n_row << ' ' << m.n_col << endl;
    for (int i = 0; i < m.n_row; ++i)
    {
        cout << "row [" << i << "] = " << m.at(i) << endl;
    }
    return cout;
}
// }}}
signed main(void)
{
    int N;
    while(cin >> N)
    {
        Point root; 
        cin >> root;
        vector<Point>p(N); 
        for(int i = 0; i < N; i++)
        {
            cin >> p[i]; 
        }
        cout << fixed << setprecision(10); 
        for(int i = 1; i + 1 < N; i++)
        {
            Matrix<double>mat(3, 4);
            mat[0][0] = p[0].x; mat[0][1] = p[i].x; mat[0][2] = p[i + 1].x; mat[0][3] = root.x; 
            mat[1][0] = p[0].y; mat[1][1] = p[i].y; mat[1][2] = p[i + 1].y; mat[1][3] = root.y; 
            mat[2][0] = mat[2][1] = mat[2][2] = mat[2][3] = 1.0; 
            auto ret = mat.gauss(); 
            if(ret[0][0] == 0 || ret[1][1] == 0 || ret[2][2] == 0) continue; 
            double alphaf = ret[0][3] / ret[0][0];
            double alphas = ret[1][3] / ret[1][1]; 
            double alphat = ret[2][3] / ret[2][2]; 
            if(alphaf >= 0 && alphas >= 0 && alphat >= 0)
            {
                cout << alphaf << '\n'; 
                for(int j = 1; j < i; j++)
                {
                    cout << 0 << '\n'; 
                }
                cout << alphas << '\n' << alphat << '\n';
                for(int j = i + 2; j < N; j++)
                {
                    cout << 0 << '\n'; 
                }
                break; 
            }
        }
    }
    return 0;
}