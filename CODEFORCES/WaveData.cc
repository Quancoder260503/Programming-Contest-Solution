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
	 jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
   }	
 }
 T query(int a, int b) {
  if(a >= b) return 0; 
  int dep = 31 - __builtin_clz(b - a);
  return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
 }
};
set<pair<int, int>>ms[2]; 
 
int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n, q, T; 
 for(cin >> T; T--; ) { 
  cin >> n >> q;
  vector<int>h(n + 1); 
  for(int i = 1; i <= n; i++) { 
   cin >> h[i]; 
  }
  ms[0].clear(); ms[1].clear(); 
  auto check = [&]() { 
   if(ms[0].size() == 0 || ms[1].size() == 0) return true; 
   auto it = ms[0].begin(); 
   int min_a = it->first; 
   it = prev(ms[0].end()); 
   int max_a = it->first; 
   it = ms[1].begin(); 
   int min_b = it->first; 
   it = prev(ms[1].end()); 
   int max_b = it->first; 
  // cerr << ms[0].size() << " " << ms[1].size() << " " << min_a << " " << max_a << " " << min_b << " " << max_b << '\n'; 
   return (min_a > max_b || min_b > max_a); 
  }; 
  vector<int>jmp(n + 7), cc; 
  for(int i = 1, r = 0; i <= n; i++) { 
   while(r < n) { 
    r++; 
    ms[r & 1].insert({h[r], r}); 
    if(!check()) { 
     r--; 
     break; 
    }
   }
   jmp[i] = r; 
   cc.push_back(r - i + 1); 
   ms[i & 1].erase({h[i], i}); 
  }
  //cout << '\n'; 
  RMQ<int>rmq(cc);
  for(int i = 0, L, R; i < q; i++) { 
   cin >> L >> R; 
   int lo = L, hi = R; 
   while(lo < hi) { 
    int mid = (lo + hi + 1) / 2; 
    if(jmp[mid] <= R) { 
     lo = mid; 
    } else { 
     hi = mid - 1; 
    }
   }
   if(jmp[lo] > R) { lo--; }
   int ret = 0; 
  /// cout << lo << " " << jmp[lo] << " " << cc[lo - 1] << '\n'; 
   ret = max(ret, rmq.query(L - 1, lo)); 
   if(lo + 1 <= R) { 
    ret = max(ret, R - lo); 
   }
   cout << ret << '\n'; 
  } 
 }
 
 return 0; 
}