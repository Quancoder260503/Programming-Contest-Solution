#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define rep(i, j, k) for(int i = j; i < k; i++)

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
  int n, T; 
  for(cin >> T; T--; ) { 
   cin >> n; 
   vector<int>a(n), b(n); 
   for(int i = 0; i < n; i++) { 
    cin >> a[i]; 
   }
   for(int i = 0; i < n; i++) { 
    cin >> b[i]; 
   }
   vector<int>c(n); 
   for(int i = 0; i < n; i++) { 
    c[i] = abs(a[i] - b[i]); 
   }
   RMQ<int>rmq(c); 
   pair<int, int>ret = {-1, -1}; 
   for(int i = 0; i < n; i++) { 
    int lo = i, hi = n; 
    while(lo < hi) { 
     int mid = (lo + hi + 1) / 2;
     if(rmq.query(i, mid) != 1) { 
      lo = mid; 
     } else { 
       hi = mid - 1; 
     }
    }
    //cout << i << " " << lo << " " << rmq.query(i, lo) << '\n'; 
    if(lo > i && rmq.query(i, lo) != 1) { 
     if(ret.first < lo - i) { 
      ret = {lo - i, rmq.query(i, lo)}; 
     } else if(ret.first == lo - i) { 
      ret.second = max(ret.second, rmq.query(i, lo)); 
     }
    }
   }
   if(ret.first == -1) cout << ret.first << '\n'; 
   else cout << ret.first << " " << ret.second << '\n'; 
  }
  return 0; 
}