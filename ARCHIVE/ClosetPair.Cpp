#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
#define double long double
const long long INF = 1e19 + 1;
typedef pair<int,int> pii;
int n;
int a[N + 1]; 
const double eps = 1e-9;
struct Vec {
    long long x, y;
    Vec(long long _x = 0, long long _y = 0) : x(_x), y(_y) {}
    long long dot(const Vec &other) {
        return x * other.x + y * other.y;
    }
    long long cross(const Vec &other) {
        return x * other.y - y * other.x;
    }
    long long length() const {
        return sqrt(x * x + y * y);
    }
};
using Point = Vec;
long long dist(Point A, Point B){
     return (1ll) * (A.x - B.x) * (A.x - B.x) + (1ll) * (A.y - B.y) * (A.y - B.y); 
}
bool cmpx(Point &a, Point &b){
     if(a.x != b.x) return a.x < b.x; 
     return a.y < b.y;
}
struct cmpy{
     bool operator () (const Point &a, const Point &b) const {
         if(a.y != b.y) return a.y < b.y; 
         return a.x < b.x;
     }
};
signed main(){
      scanf("%d",&n);
      Point points[N + 1]; 
      for(int i = 0; i < n; i++){
            cin >> points[i].x >> points[i].y;
      }
      sort(points, points + n, cmpx);
      set<Point,cmpy>setp; 
      long long dis = INF;
      for(int i = 0; i < n; i++){
            long long x = points[i].x;
            long long y = points[i].y; 
            long long d = sqrt(dis);
            Point cur = {-INF,y - d};
            while(true){
                auto it = setp.upper_bound(cur);
                if(it == setp.end()){
                     break; 
                } 
                cur = *it;
                if(cur.y > y + d) break;
                if(cur.x < x - d){
                      setp.erase(it); 
                      continue;
                }
                dis = min(dis, dist(cur,points[i])); 
            }
            setp.insert(points[i]); 
      }
      printf("%lld\n",dis); 
      return 0;
}