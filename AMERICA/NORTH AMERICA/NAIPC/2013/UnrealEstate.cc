#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

template <class T>
struct LazySeg {
  int sz;
  vector<T> st, ycoord;
  vector<int>lz; 
  T comb(T a, T b) { return a + b; }
  LazySeg(int n, vector<T> &_ycoord) : ycoord(_ycoord) {
    sz = 1;
    while (sz < n) sz <<= 1;
    st.assign(4 * sz, 0); lz.assign(4 * sz, 0); 
    return; 
  }
  T length(int ql, int qr) { 
    return ycoord[qr] - ycoord[ql]; 
  }
  void pull(int i, int ql, int qr) { 
    if(lz[i] < 1) st[i] = (ql + 1 == qr ? 0 : comb(st[i << 1], st[i << 1 | 1]));
    else st[i] = length(ql, qr); 
    return; 
  }
  void update(int ql, int qr, int x, int i, int l, int r) {
    if (ql >= r || qr <= l) return;
    if (ql <= l && r <= qr) {
      lz[i] += x; 
    }
    else { 
      int m = (l + r) >> 1;
      update(ql, qr, x, i << 1, l, m);
      update(ql, qr, x, i << 1 | 1, m, r);
    }
    pull(i, l, r);
    return; 
  }
  void update(int ql, int qr, int x) { update(ql, qr, x, 1, 0, sz - 1); }
  /* 
  T query(int ql, int qr, int i, int l, int r) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && qr >= r) return st[i];
    int m = (l + r) >> 1;
    return comb(query(ql, qr, i << 1, l, m),
                query(ql, qr, i << 1 | 1, m + 1, r));
  }
  T query(int ql, int qr) { return query(ql, qr, 1, 0, sz - 1); }
  */
};

struct event { 
  double x; 
  int type, ylo, yhi;
  event(double _x, int _ylo, int _yhi, int _type):  x(_x), ylo(_ylo), yhi(_yhi), type(_type) {} 
  bool operator < (const event &other) const { 
    if(fabs(x - other.x) > 1e-6) return x < other.x;
    return type < other.type; 
  }
}; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N; 
  cout << fixed << setprecision(2); 
  while(cin >> N && N) { 
    vector<tuple<double, double, double, int>>_stick; 
    vector<double>ycoord;
    for(int i = 0; i < N; i++) { 
      double xA, xB, yA, yB; 
      cin >> xA >> yA >> xB >> yB; 
      _stick.push_back({xA, yA, yB, 1}); 
      _stick.push_back({xB, yA, yB, -1});
      ycoord.push_back(yA); 
      ycoord.push_back(yB);  
    }
    sort(ycoord.begin(), ycoord.end()); 
    ycoord.erase(unique(ycoord.begin(), ycoord.end()), ycoord.end()); 
    vector<event>stick;
    for(auto [x, yA, yB, type] : _stick) { 
      int pA = lower_bound(ycoord.begin(), ycoord.end(), yA) - ycoord.begin(); 
      int pB = lower_bound(ycoord.begin(), ycoord.end(), yB) - ycoord.begin(); 
      stick.push_back(event(x, pA, pB, type)); 
    }
    sort(stick.begin(), stick.end()); 
    LazySeg<double>tree(sz(ycoord), ycoord);
    double ret = 0; 
    for(int i = 0; i < sz(stick) - 1; i++) { 
      tree.update(stick[i].ylo, stick[i].yhi, stick[i].type); 
      ret += (-stick[i].x + stick[i + 1].x) * tree.st[1];
    }
    cout << ret << '\n'; 
  }
  return 0; 
}