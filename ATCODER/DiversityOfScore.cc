#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
 ios_base::sync_with_stdio(0); 
 cin.tie(0);
 cout.tie(0);  
 int N, T; 
 cin >> N >> T; 
 vector<int64_t>c(N); 
 unordered_map<int64_t, int>mp;
 mp[0] = N; 
 for(int i = 0, a, b; i < T; i++) { 
  cin >> a >> b;
  --a; 
  mp[c[a]]--; 
  if(mp[c[a]] == 0) mp.erase(c[a]); 
  c[a] += b; 
  mp[c[a]]++; 
  cout << sz(mp) << '\n'; 
 } 
 return 0; 
}