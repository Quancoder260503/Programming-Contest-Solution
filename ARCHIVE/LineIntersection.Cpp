#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
#define double long double
typedef pair<int,int> pii;
int n;
int a[N + 1]; 
const double eps = 1e-9;
struct Vec {
    double x, y;
    Vec(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    double dot(const Vec &other) {
        return x * other.x + y * other.y;
    }
    double cross(const Vec &other) {
        return x * other.y - y * other.x;
    }
    double length() const {
        return sqrt(x * x + y * y);
    }
};
using Point = Vec;
Vec operator - (const Point &B, const Point &A) { 
    return Vec(B.x - A.x, B.y - A.y);
}
int sign(double x) {
    if (x > eps) return 1;
    if (x < -eps) return -1;
    return 0;
}
double cross(Vec AB, Vec AC) {
    return AB.x * AC.y - AC.x * AB.y;
}
double dot(Vec AB, Vec AC) {
    return AB.x * AC.x + AB.y * AC.y;
}
bool intersect(Point A, Point B, Point C, Point D) {
    int ABxAC = sign(cross(B - A, C - A));
    int ABxAD = sign(cross(B - A, D - A));
    int CDxCA = sign(cross(D - C, A - C));
    int CDxCB = sign(cross(D - C, B - C));
    if (ABxAC == 0 || ABxAD == 0 || CDxCA == 0 || CDxCB == 0) {
        if (ABxAC == 0 && sign(dot(A - C, B - C)) <= 0) return true;
        if (ABxAD == 0 && sign(dot(A - D, B - D)) <= 0) return true;
        if (CDxCA == 0 && sign(dot(C - A, D - A)) <= 0) return true;
        if (CDxCB == 0 && sign(dot(C - B, D - B)) <= 0) return true;
        return false;
    }
    return (ABxAC * ABxAD < 0 && CDxCA * CDxCB < 0);
}
signed main(){
      scanf("%d",&n);
      for(int i = 0; i < n; i++){
          Point A,B,C,D;  
          cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y;
          cout << (intersect(A,B,C,D) ? "YES" : "NO") << endl; 
      }
      return 0;
}