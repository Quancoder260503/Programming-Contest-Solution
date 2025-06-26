#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
#define double long double
const long long INF = 1e14 + 1;
typedef pair<int,int> pii;
int n,q;
int a[N + 1]; 
const double eps = 1e-9;
struct Vec {
    long long x, y;
    Vec(long long _x = 0, long long _y = 0) : x(_x), y(_y){}
    long long dot(const Vec &other) const {
        return x * other.x + y * other.y;
    }
    long long cross(const Vec &other) const {
        return x * other.y - y * other.x;
    }
    bool operator < (const Vec &a) const { 
         return cross(a) > 0;
    }
    Vec operator - (const Vec &a) const { 
         return Vec(x - a.x, y - a.y); 
    }
    long long length() const {
        return sqrt(x * x + y * y);
    }
};
using Point = Vec;
Point cur;
Point points[N + 1]; 
bool cmpy(Point &a, Point &b){
     return a.y == b.y ? a.x < b.x : a.y < b.y;
}
signed main(){
      scanf("%d",&n);
      for(int i = 1; i <= n; i++) cin >> points[i].x >> points[i].y;
      long long area = 0;
      long long boundary = 0;
      for(int i = 1; i <= n; i++){
           int nxt = (i == n ? 1 : i + 1); 
           long long h = abs(points[i].x - points[nxt].x); 
           long long v = abs(points[i].y - points[nxt].y);   
           if(h == 0) boundary += v;
           else if(v == 0) boundary += h;
           else boundary += gcd(h,v); 
           area += (1ll) * points[i].x * points[nxt].y; 
           area -= (1ll) * points[i].y * points[nxt].x; 
      }
      if(area < 0) area = - area;
      long long inside = (area - boundary + 2) / 2;
      cout << inside << ' ' << boundary << endl;
      return 0;
}