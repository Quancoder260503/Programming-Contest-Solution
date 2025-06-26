#include "bits/stdc++.h"

using namespace std;

#define sz(x) x.size()
#define all(x) x.begin(), x.end()

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

typedef long long T;
typedef Point3D<T> P;
const T INF = numeric_limits<T>::max();

bool on_x(const P &a, const P &b) { return a.x < b.x; }
bool on_y(const P &a, const P &b) { return a.y < b.y; }
bool on_z(const P &a, const P &b) { return a.z < b.z; }

struct Node
{
    P pt;                                       // if this is a leaf, the single point in it
    T x0 = INF, x1 = -INF, y0 = INF, y1 = -INF, z0 = INF, z1 = -INF; // bounds
    Node *first = 0, *second = 0;

    T distance(const P &p)
    { // min squared distance to a point
        T x = (p.x < x0 ? x0 : p.x > x1 ? x1 : p.x);
        T y = (p.y < y0 ? y0 : p.y > y1 ? y1 : p.y);
        T z = (p.z < z0 ? z0 : p.z > z1 ? z1 : p.z); 
        return (P(x, y, z) - p).dist2();
    }

    Node(vector<P> &&vp) : pt(vp[0])
    {
        for (P p : vp)
        {
            x0 = min(x0, p.x);
            x1 = max(x1, p.x);
            y0 = min(y0, p.y);
            y1 = max(y1, p.y);
            z0 = min(z0, p.z);
            z1 = max(z1, p.z);  
        }
        if (vp.size() > 1)
        {
            // split on x if width >= height (not ideal...)
            sort(all(vp), x1 - x0 >= y1 - y0 ? on_x : (y1 - y0 >= z1 - z0 ? on_y : on_z));
            // divide by taking half the array for each child (not
            // best performance with many duplicates in the middle)
            int half = sz(vp) / 2;
            first = new Node({vp.begin(), vp.begin() + half});
            second = new Node({vp.begin() + half, vp.end()});
        }
    }
};

struct KDTree
{
    Node *root;
    KDTree(const vector<P> &vp) : root(new Node({all(vp)})) {}

    pair<T, P> search(Node *node, const P &p)
    {
        if (!node->first)
        {
            // uncomment if we should not find the point itself:
            if (p == node->pt) return {INF, P()};
            return make_pair((p - node->pt).dist2(), node->pt);
        }
        Node *f = node->first, *s = node->second;
        T bfirst = f->distance(p), bsec = s->distance(p);
        if (bfirst > bsec)
            swap(bsec, bfirst), swap(f, s);

        // search closest side first, other side if needed
        auto best = search(f, p);
        if (bsec < best.first)
            best = min(best, search(s, p));
        return best;
    }

    // find nearest point to a point, and its squared distance
    // (requires an arbitrary operator< for Point)
    pair<T, P> nearest(const P &p)
    {
        return search(root, p);
    }
};


int main(void)
{
    int N; 
    cin >> N; 
    vector<P>p(N); 
    for(int i = 0; i < N; i++) cin >> p[i].x >> p[i].y >> p[i].z; 
    KDTree kd(p); 
    T ret = INT64_MAX; 
    for(int i = 0; i < N; i++)
    {
        auto dist = kd.nearest(p[i]); 
        ret = min(ret, dist.first); 
    }
    cout << fixed << setprecision(10) << sqrt(ret) << '\n'; 
    return 0; 
}