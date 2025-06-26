#include "bits/stdc++.h"

using namespace std;
const double INF = 1e9; 
const int Round = 1000; 

template <class T>
struct Point3D
{
    typedef Point3D P;
    typedef const P &R;
    T x, y, z;
    explicit Point3D(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
    bool operator<(R p) const
    {
        return tie(x, y, z) < tie(p.x, p.y, p.z);
    }
    bool operator==(R p) const
    {
        return tie(x, y, z) == tie(p.x, p.y, p.z);
    }
    P operator+(R p) const { return P(x + p.x, y + p.y, z + p.z); }
    P operator-(R p) const { return P(x - p.x, y - p.y, z - p.z); }
    P operator*(T d) const { return P(x * d, y * d, z * d); }
    P operator/(T d) const { return P(x / d, y / d, z / d); }
    T dot(R p) const { return x * p.x + y * p.y + z * p.z; }
    P cross(R p) const
    {
        return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }
    T dist2() const { return x * x + y * y + z * z; }
    double dist() const { return sqrt((double)dist2()); }
    // Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
    double phi() const { return atan2(y, x); }
    // Zenith angle (latitude) to the z-axis in interval [0, pi]
    double theta() const { return atan2(sqrt(x * x + y * y), z); }
    P unit() const { return *this / (T)dist(); } // makes dist()=1
    // returns unit vector normal to *this and p
    P normal(P p) const { return cross(p).unit(); }
    // returns point rotated 'angle' radians ccw around axis
    P rotate(double angle, P axis) const
    {
        double s = sin(angle), c = cos(angle);
        P u = axis.unit();
        return u * dot(u) * (1 - c) + (*this) * c - cross(u) * s;
    }
    friend ostream &operator<<(ostream &os, P p)
    {
        return os << "(" << p.x << "," << p.y << "," << p.z << ")";
    }
};

typedef Point3D<double> P;

double segDist(P &s, P &e, P &p)
{
    if (s == e) return (p - s).dist();
    auto d = (e - s).dist2(), t = min(d, max(.0, (p - s).dot(e - s)));
    return ((p - s) * d - (e - s) * t).dist() / d;
}

P src, to;
int N;

int main(void)
{
    auto dist = [&](P s, P e, P a) -> double
    {
        return segDist(s, e, a);
    };
    cout << fixed << setprecision(7); 
    while(cin >> src.x >> src.y >> src.z >> to.x >> to.y >> to.z >> N)
    {
        for(int i = 0; i < N; i++)
        {
            P at, dir; 
            int M; 
            cin >> at.x >> at.y >> at.z >> dir.x >> dir.y >> dir.z >> M;
            double max_dist = 0.0; 
            for(int j = 0; j < M; j++)
            {
                P curr; 
                cin >> curr.x >> curr.y >> curr.z; 
                max_dist = max(max_dist, (at - curr).dist());
            }
            double L = 0; 
            double R = INF;
            for(int j = 0; j < Round; j++)
            {
                double x1 = (2 * L + R) / 3.0; 
                double x2 = (L + 2 * R) / 3.0;
                if (dist(src, to, at + dir * x1) < dist(src, to, at + dir * x2)) R = x2;
                else L = x1;
            }
            if(dist(src, to, at + dir * L) < max_dist)
            {
                cout << "Surrender" << '\n'; 
                return 0; 
            }
        }
        cout << "Go" << '\n'; 
    }
    return 0;
}