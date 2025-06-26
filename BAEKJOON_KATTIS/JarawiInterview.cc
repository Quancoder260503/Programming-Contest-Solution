#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 string s; 
 cin >> s;
 s = " " + s; 
 int n = sz(s); 
 vector<vector<int>>nxt(n, vector<int>(26, -1)); 
 for(int i = 1; i < sz(s); i++) {
  for(int j = i - 1; j >= 0; j--) { 
   nxt[j][s[i] - 'a'] = i; 
   if(s[i] == s[j]) break; 
  } 
 } 
 int q; 
 cin >> q; 
 for(int i = 0; i < q; i++) {
  auto isSubseq = [&](string c) {
   for(int j = 0, pos = 0; j < sz(c); j++) {
    if(nxt[pos][c[j] - 'a'] == -1) return false; 
    pos = nxt[pos][c[j] - 'a']; 
   }
   return true; 
  };
  string c; cin >> c;
  int lo = 0, hi = sz(c); 
  while(lo < hi) {
   int mid = (lo + hi) / 2; 
   string p = c.substr(mid); 
   if(isSubseq(p)) hi = mid; 
   else lo = mid + 1; 
  }
  cout << (sz(c) - lo) << '\n'; 
 } 
 return 0;
}