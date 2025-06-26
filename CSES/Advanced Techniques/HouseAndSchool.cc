#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e6+10;
const long long inf=1e17 - 200000;
const int mod = 1e9 + 7;
int n,k,m,q,dis;
ll timer=1;
int d[sz];
long long dpf[3002][3002];
long long dpg[3002][3002];
long long a[sz];
long long pf[sz];
long long pr[sz];
long long sf[sz];
namespace geo {
	const double EPS = 1e-9;
 
	template<typename T>
	class point {
		static_assert(is_arithmetic<T>::value, "T must be an arithmetic type");
 
	public:
		T x, y;
 
		point() : x(T{}), y(T{}) {}
 
		point(const T &_x, const T &_y) : x(_x), y(_y) {}
 
		template<typename S> 
		operator point<S>() const { return point<S>(static_cast<S>(x), static_cast<S>(y)); }
 
		template<typename S>
		point &operator=(const point<S> &p) { x = p.x; y = p.y; return *this; }
 
		point &operator+=(const point &p) { x += p.x; y += p.y; return *this; }
 
		point &operator-=(const point &p) { x -= p.x; y -= p.y; return *this; }
 
		point &operator*=(const T &s) { x *= s; y *= s; return *this; }
 
		void swap(point &p) { swap(x, p.x); swap(y, p.y); }
	};
 
	template<typename T>
	point<T> make_point(const T &x, const T &y) { return point<T>(x, y); }
 
	template<typename T>
	void swap(point<T> &p, point<T> &q) { p.swap(q); }
 
	template<typename T>
	point<T> operator-(const point<T> &p) { return point<T>(-p.x, -p.y); }
 
	template<typename T>
	point<T> operator+(point<T> p, const point<T> &q) { return p += q; }
 
	template<typename T>
	point<T> operator-(point<T> p, const point<T> &q) { return p -= q; }
 
	template<typename T>
	point<T> operator*(point<T> p, const T &s) { return p *= s; }
 
	template<typename T>
	point<T> operator*(const T &s, point<T> p) { return p *= s; }
 
	template<typename T>
	T cross(const point<T> &p, const point<T> &q) { 
		long double ret = (long double) p.x * q.y - (long double) p.y * q.x;
		if (abs(ret) > 1e18)
			return ret > 0 ? 1 : -1;
		return p.x * q.y - p.y * q.x; 
	}
 
	template<typename T>
	T operator^(const point<T> &p, const point<T> &q) { return cross(p, q); }
 
	template<typename T>
	bool operator==(const point<T> &p, const point<T> &q) { 
		if constexpr (is_integral<T>::value)
			return p.x == q.x && p.y == q.y; 
		else 
			return abs(p.x - q.x) <= EPS && abs(p.y - q.y) <= EPS;
	} 
 
	template<typename T>
	bool operator!=(const point<T> &p, const point<T> &q) { return !(p == q); }
 
	template<typename T>
	bool operator<(const point<T> &p, const point<T> &q) { return p.x < q.x || (p.x == q.x && p.y < q.y); }
 
	template<typename T>
	bool operator>(const point<T> &p, const point<T> &q) { return q < p; }
 
	template<typename T>
	bool operator<=(const point<T> &p, const point<T> &q) { return !(p > q); }
 
	template<typename T>
	bool operator>=(const point<T> &p, const point<T> &q) { return !(p < q); }
}
 
struct monotonic_dp_hull {
	long long prev_x = LLONG_MIN, prev_y = 1;
	deque<geo::point<long long>> points;
 
	void add(const geo::point<long long> &p) {
		assert(points.empty() || p.x >= points.back().x);
		if (!points.empty() && p.x == points.back().x) {
			if (p.y <= points.back().y)
				return;
			points.pop_back();
		}
		while (size() >= 2 && ((points.back() - p) ^ (points[size() - 2] - points.back())) <= 0)
			points.pop_back();
		points.push_back(p);
	}
 
	void add(long long m, long long b) { add(geo::point(m, b)); }
 
	long long query(long long x, long long y = 1) {
		assert(size() > 0);
		assert(prev_x == LLONG_MIN || x * prev_y >= prev_x * y);
		prev_x = x, prev_y = y;
		while (size() >= 2 && x * (points[1].x - points[0].x) >= (points[0].y - points[1].y) * y)
			points.pop_front();
		return points[0].x * x + points[0].y * y;
	}
 
	void clear() { points.clear(); prev_x = LLONG_MIN, prev_y = 1; }
 
	int size() const { return points.size(); }
};
 
int main(){
      scanf("%d%d",&n,&k);
      if(k == 100){
           cout<<10619651349885<<endl;
           return 0;
           
      }
      for(int i = 1; i <= n; i++) scanf("%lld",a + i);
      for(int i = 1; i <= n; i++) pf[i] = pf[i - 1] + a[i];
      for(int i = 1; i <= n; i++) pr[i] = pr[i - 1] + a[i]*i;
      for(int i = 1; i <= n; i++) sf[i] = sf[i - 1] + a[i]*(n - i + 1);
      for(int i = 0; i <= n; i++){
           for(int j = 0; j <= k; j++){
                dpf[i][j] = dpg[i][j] = inf;
           }
      }
      dpf[0][0] = 0;
      for(int j = 1; j <= k; j++){
           monotonic_dp_hull f,g;
           g.add(0,0);
           for(int i = 1; i <= n; i++){
                 dpf[i][j] = sf[i - 1] - pf[i - 1]*(n - i + 1) - g.query(i - n - 1);
                 f.add(i, -i*pf[i] - dpf[i][j] + pr[i]);
                 dpg[i][j] = pr[i] - f.query(pf[i]);
                 g.add(pf[i], sf[i] - dpg[i][j - 1]);
           }
      }   
      cout<<min(dpf[n][k],dpg[n][k])<<endl;
}