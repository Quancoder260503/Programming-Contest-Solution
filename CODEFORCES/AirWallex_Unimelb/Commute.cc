#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
const int64_t oo = 1e18 + 10; 

const double eps = 1e-7; 
 
class Commute { 
 public :
   void solve() { 
    double L, a, b, c, d; 
    cin >> L >> a >> c >> b >> d; 
    auto f = [&](double x) { 
     return a * x * x + c; 
    }; 
    auto g = [&](double x) { 
     return b * x * x + d; 
    }; 
    auto h = [&](double x) { 
     return f(x) + g(L - x);  
    }; 
    double lo = 0.0, hi = L; 
    for(int cc = 0; cc < 100; cc++) { 
     double x1 = (2 * lo + hi) / 3.0; 
     double x2 = (lo + 2 * hi) / 3.0; 
     if(h(x1) < h(x2)) { 
      hi = x2; 
     } else { 
      lo = x1; 
     }
    }
    if(f(L) < h(lo)) { 
     cout << "-1" << '\n'; 
    } 
    else { 
     cout << fixed << setprecision(10) << lo << '\n'; 
    } 
    return; 
   }
}; 
 
int main(void) { 
  Commute comm; 
  comm.solve(); 
  return 0; 
}