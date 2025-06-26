#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
#define double long double
const long long INF = 1e14 + 1;
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
signed main(){
      scanf("%d",&n);
      Point points[N + 1]; 
      for(int i = 0; i < n; i++) cin >> points[i].x >> points[i].y;
      long long ans = 0;
      for(int i = 0; i < n - 1; i++){
           ans += (1ll) *points[i].x * points[i + 1].y;
           ans -= (1ll) * points[i + 1].x * points[i].y; 
      }
      ans += (1ll) * points[n - 1].x * points[0].y;
      ans -= (1ll) * points[0].x * points[n - 1].y; 
      if(ans < 0) ans = -ans;  
      cout << ans << endl;
      return 0;
}