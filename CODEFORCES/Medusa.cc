#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
 

int n, q; 
string s; 

 
struct FT {
  int N;
  vector<int> bit;
  FT(int _N = 0) {
    N = _N;
    bit.resize(N);
  }
  int query(int i) {
    int c = 0;
    for (++i; i > 0; i -= (i & -i)) {
      c = c + bit[i];
    }
    return c;
  }
  int query(int l, int r) { 
    if(l > r) return 0; 
    return query(r) - query(l - 1); 
  }
  void update(int i, int dif) {
    for (++i; i < N; i += (i & -i)) {
      bit[i] = dif + bit[i];
    }
  }
}; 
 
int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 cin >> n >> q >> s; 
 unordered_map<char, int>mp; 
 int cnt = 0; 
 for(auto c : {'S', 'N', 'A', 'K', 'E'}) { 
  mp[c] = cnt++; 
 }
 vector<FT> fenw; 
 for(int i = 0; i < 5; i++) { 
  fenw.push_back(FT(3 * n)); 
 }
 for(int i = 0; i < n; i++) { 
  fenw[mp[s[i]]].update(i + 1, 1); 
 }
 auto check = [&](int x) { 
  int st = 1, match = 0; 
  for(int i = 0; i < cnt; i++) { 
   if(st > n) return false;  
   int lo = st, hi = n; 
   while(lo < hi) { 
    int mid = (lo + hi) / 2; 
    if(fenw[i].query(st, mid) >= x) { 
     hi = mid; 
    } else { 
     lo = mid + 1; 
    }
   }
   match += fenw[i].query(st, lo) >= x; 
   //cout << st << " " << lo << " " << fenw[i].query(st, lo) << '\n'; 
   st = lo + 1;
  }  
  return match == cnt; 
 }; 
 for(int i = 0; i < q; i++) {
  int pos; char nxt; 
  cin >> pos >> nxt; 
  --pos; 
  fenw[mp[s[pos]]].update(pos + 1, -1); 
  s[pos] = nxt; 
  fenw[mp[s[pos]]].update(pos + 1, 1); 
  int lo = 0, hi = n + 1; 
  while(lo < hi) { 
   int mid = (lo + hi + 1) / 2; 
   if(check(mid)) { 
    lo = mid; 
   } else { 
    hi = mid - 1; 
   }
  }
  cout << lo << '\n';  
 } 
 return 0; 
}