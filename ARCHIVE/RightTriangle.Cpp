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
      for(int i = 1; i <= n; i++){
          cin >> points[i].x >> points[i].y; 
      }
      long long ans = 0;
      for(int i = 1; i <= n; i++){
         map<double,int>mp;
         long long res = 0;
         long long cnth, cntv; 
         cnth = cntv = 0;
         for(int j = 1; j <= n; j++){
              if(i == j) continue;
              double X = (points[i].x - points[j].x);
              double Y = (points[i].y - points[j].y);
              if(points[i].y == points[j].y){
                    cntv++;
                    continue; 
              }
              if(points[i].x == points[j].x){
                    cnth++; 
                    continue;
              }
              if(points[i].y != points[j].y){
                 double k = X / Y;
                 ans += mp[k];
                 k = -Y / X;
                 mp[k]++;
              }
         }
         ans += (1ll) * cnth * cntv;
      }
      cout << ans << endl;
      return 0;
}