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
long long cross(Point A,Point B){
     return A.x * B.y - A.y * B.x; 
}
bool intersect(Point A,Point B, Point C){
     if(cross(B - A, B - C) != 0) return false;
     if(min(B.x, C.x) <= A.x && A.x <= max(B.x, C.x) && min(B.y,C.y) <= A.y && A.y <= max(B .y,C.y)) return true;
     return false;
}
void execute(){
      bool bdry = 0;
      int cnt = 0;
      for(int i = 1; i <= n; i++){
           int nxt = (i == n ? 1 : i + 1); 
           if(intersect(cur,points[i],points[nxt])){
               bdry = 1; 
           }
           if(points[i].x <= cur.x && cur.x < points[nxt].x && cross(cur - points[i],cur - points[nxt]) > 0) cnt += 1; 
           else if(points[nxt].x <= cur.x && cur.x < points[i].x && cross(cur - points[nxt],cur - points[i]) > 0) cnt += 1;
     } 
     if(bdry) cout << "BOUNDARY" << endl; 
     else if(cnt & 1) cout << "INSIDE" << endl; 
     else cout << "OUTSIDE" << endl; 
}
signed main(){
      scanf("%d%d",&n,&q);
      for(int i = 1; i <= n; i++) cin >> points[i].x >> points[i].y; 
      for(int i = 0; i < q; i++){
           cin >> cur.x >> cur.y; 
           execute(); 
      } 
      return 0;
}