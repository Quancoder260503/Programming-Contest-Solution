#include "bits/stdc++.h"

using namespace std;

const int oo = 1e9; 

#define sz(x) int(x.size())

const int maxn = 1e6 + 10; 
vector<int>p; 
int vis[maxn]; 

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0); 
  vis[1] = true; 
  for(int i = 2; i < maxn; i++) { 
   if(vis[i]) continue; 
   p.push_back(i); 
   for(int j = 2 * i; j < maxn; j += i) { 
    vis[j] = 1; 
   }
  }
  vector<int>cc; 
  for(int i = 0; i < sz(p); i++) {
   for(int j = i + 1; j < sz(p) && p[i] < (10 * maxn) / p[j]; j++) { 
    cc.push_back(p[i] * p[j]); 
   } 
  }
  sort(cc.begin(), cc.end()); 
  int T, a, b, c, d; 
  for(cin >> T; T--; ) {
   cin >> a >> b >> c >> d; 

   int ac = upper_bound(cc.begin(), cc.end(), c) - lower_bound(cc.begin(), cc.end(), a); 
   int bd = upper_bound(cc.begin(), cc.end(), d) - lower_bound(cc.begin(), cc.end(), b); 
   int64_t ret = ac * (b == 1) + bd * (a == 1); 
   //cout << ac << " " << bd << '\n';  
   a = lower_bound(p.begin(), p.end(), a) - p.begin(); 
   b = lower_bound(p.begin(), p.end(), b) - p.begin(); 
   c = upper_bound(p.begin(), p.end(), c) - p.begin(); 
   d = upper_bound(p.begin(), p.end(), d) - p.begin(); 

   ret += 1LL * (c - a) * (d - b); 
   ret = ret - max(0, min(c, d) - max(a, b)); 
   cout << ret << '\n'; 
  } 

  return 0;
}