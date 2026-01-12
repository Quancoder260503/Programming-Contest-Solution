#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

using ll = long long;

int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n, m; 
 cin >> n >> m; 
 int max_id = 0; 
 vector<int>a(n); 
 for(auto &x : a) { 
  cin >> x; 
  max_id = max(max_id, x); 
 }
 vector<vector<int>>cc(max_id + 1); 
 for(int i = 0; i < n; i++) { 
  cc[a[i]].push_back(i + 1); 
 }
 cc[0].push_back(0); 
 ll total = 0;
 ll possible = 0; 
 for(int i = 1; i <= max_id; i++) { 
  if(sz(cc[i]) == 0) { 
   cout << "Impossible\n"; 
   exit(0); 
  } 
  total += sz(cc[i]);
  possible += 1LL * sz(cc[i]) * (sz(cc[i]) - 1) + 1LL * sz(cc[i]) * sz(cc[i - 1]);  
 }
 if(total > m || possible < m) { 
  cout << "Impossible\n"; 
 }
 vector<pair<int, int>>ret;
 for(int i = 1; i <= max_id; i++) { 
  for(auto &x : cc[i]) { 
   ret.push_back({cc[i - 1][0], x});
  } 
 }  
 if(sz(ret) == m) { 
  cout << "Possible\n"; 
  for(auto [v1, v2] : ret) cout << v1 << " " << v2 << '\n';  
  exit(0);  
 }
 for(int i = 1; i <= max_id; i++) { 
  for(int j = 1; j < sz(cc[i - 1]); j++) { 
   for(auto &y : cc[i]) { 
    ret.push_back({cc[i - 1][j], y}); 
    if(sz(ret) == m) {
     cout << "Possible\n"; 
     for(auto [v1, v2] : ret) cout << v1 << " " << v2 << '\n';  
     exit(0); 
    }
   }
  }
  for(int j = 0; j < sz(cc[i]); j++) { 
   for(int k = j + 1; k < sz(cc[i]); k++) { 
    ret.push_back({cc[i][j], cc[i][k]}); 
    if(sz(ret) == m) {
     cout << "Possible\n"; 
     for(auto [v1, v2] : ret) cout << v1 << " " << v2 << '\n';  
     exit(0); 
    }
   }
  }
 }
 cout << "Impossible\n"; 
 return 0; 
}
