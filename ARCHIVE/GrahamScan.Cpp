#include <bits/stdc++.h>
using namespace std;
#define N 1500000
const int mod = 1e9 + 7; 
long long finv[N];
long long fac[N];
long long inv[N]; 
int n,k;  
// Graham Scan only work on non colinear - convex
struct Vec {
    long long x, y;
    Vec(long long _x = 0, long long _y = 0) : x(_x), y(_y) {}
    long long dot(const Vec &other) const {
        return x * other.x + y * other.y;
    }
    long long cross(const Vec &other) const {
        return x * other.y - y * other.x;
    }
    bool operator < (const Vec &a) const { 
            return  x == a.x  ? y < a.y : x < a.x;
    }
    Vec operator - (const Vec &a) const { 
         return Vec(x - a.x, y - a.y); 
    }
    long long length() const {
        return sqrt(x * x + y * y);
    }
    long long norm() const {
        return x * x + y * y; 
    }
};
long long cross3(Vec AB, Vec AC, Vec BC) {
    Vec X = AC - AB; 
    Vec Y = BC - AB; 
    return  X.cross(Y);
}
using Point = Vec;
Point P[N]; 
vector<int> GrahamScan(vector<Point>& Pset){
        int mpos = min_element(Pset.begin(), Pset.end()) - Pset.begin();
        vector<int>cand;
        vector<int>hull {mpos};
        for(int i = 0; i < Pset.size(); i++){
              if(Pset[mpos].x == Pset[i].x && Pset[mpos].y == Pset[i].y) continue; 
              cand.push_back(i); 
        }
        sort(cand.begin(),cand.end(), [&] (int a, int b){
             Vec A = Pset[a] - Pset[mpos]; 
             Vec B = Pset[b] - Pset[mpos];
             int p = A.cross(B); 
             return p == 0 ? A.norm() < B.norm() : p > 0; 
        }); 
        for(int i = 0; i < cand.size(); i++){ 
              while(hull.size() > 1 && cross3(Pset[hull[hull.size() - 2]],Pset[hull.back()], Pset[cand[i]]) < 0){
                   hull.pop_back(); 
             }
             hull.push_back(cand[i]); 
        }
        return hull; 
}
void solve(){
     vector<Point>Pset;
     for(int i = 0; i < n; i++){
          cin >> P[i].x >> P[i].y;
          Pset.push_back(P[i]); 
     }
     vector<int>cvhull = GrahamScan(Pset); 
     cout << (int) cvhull.size() << endl; 
     for(int i = 0; i < cvhull.size(); i++){
           cout << P[cvhull[i]].x << ' ' << P[cvhull[i]].y << endl; 
     }
     return; 
}
signed main(void){
     cin >> n;
     solve(); 
     return 0; 
}