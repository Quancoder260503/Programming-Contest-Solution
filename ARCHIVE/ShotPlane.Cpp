#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
#define double long double
const long long INF = 1e14 + 1;
typedef pair<int,int> pii;
int n;
int a[N + 1]; 
int cnt[N + 1]; 
const double eps = 1e-9;
struct Vec {
    long long x, y, id;
    Vec(long long _x = 0, long long _y = 0,long long _id = 0) : x(_x), y(_y), id(_id) {}
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
         return Vec(x - a.x, y - a.y, id); 
    }
    long long length() const {
        return sqrt(x * x + y * y);
    }
};
long long cross(Vec AB, Vec AC) {
    return AB.x * AC.y - AC.x * AB.y;
}
using Point = Vec;
bool cmpy(Point &a, Point &b){
     return a.y == b.y ? a.x < b.x : a.y < b.y;  
}
signed main(){
      scanf("%d",&n);
      Point points[N + 1]; 
      Point b[N + 1]; 
      for(int i = 1; i <= n; i++){
           cin >> points[i].x >> points[i].y; 
           points[i].id = i; 
      }
      sort(points + 1, points + n + 1,cmpy); 
      long long ans = 0;
      for(int i = 1; i <= n; i++){
            int m = 0;
            for(int j = 1; j < i; j++){
                 b[m++] = points[j] - points[i]; 
            }
            for(int j = 0; j < m; j++){
                 for(int k = j + 1; k < m; k++){
                      if(b[j].cross(b[k]) != 0){
                            ans++; 
                            cnt[points[i].id]++;
                            cnt[b[j].id]++;
                            cnt[b[k].id]++;
                      }
                 }
            }
      }
      pair<long long,long long>res{INF,0};
      for(int i = 1; i <= n; i++){
           res = min(res, {cnt[i],i}); 
      }
      cout << ans << ' ' << res.second << endl; 
      return 0;
}