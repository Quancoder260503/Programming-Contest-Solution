#include "bits/stdc++.h"
 
using namespace std; 
 
#define rep(i, j, k) for(int i = j; i < k; i++)
#define sz(x) int(x.size())
 
template<class T>
struct RMQ {
 vector<vector<T>> jmp;
 RMQ(const vector<T>& V) : jmp(1, V) {
  for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
   jmp.emplace_back(sz(V) - pw * 2 + 1);
   rep(j,0,sz(jmp[k]))
	 jmp[k][j] = gcd(jmp[k - 1][j], jmp[k - 1][j + pw]);
   }	
 }
 T query(int a, int b) {
  if(a >= b) return 0; 
  int dep = 31 - __builtin_clz(b - a);
  return gcd(jmp[dep][a], jmp[dep][b - (1 << dep)]);
 } 
};

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T; 
  for(cin >> T; T--; ) { 
   int n; 
   cin >> n; 
   vector<int>a(2 * n); 
   for(int i = 0; i < n; i++) { 
    cin >> a[i]; 
    a[n + i] = a[i]; 
   } 
   int g = a[0]; 
   for(int i = 0; i < n; i++) { 
    g = gcd(g, a[i]); 
   }
   for(int i = 0; i < 2 * n; i++) { 
    a[i] = a[i] / g; 
   }
   RMQ<int>rmq(a); 
   int ret = 0; 
   for(int i = 0; i < n; i++) { 
    int lo = i, hi = i + n;
    while(lo < hi) { 
     int mid = (lo + hi) / 2; 
     if(rmq.query(i, mid) == 1) { 
      hi = mid;   
     } else {
      lo = mid + 1; 
     }
    }
    ret = max(ret, lo - i - 1);  
   }
   cout << ret << '\n'; 
  }
  return 0; 
}


