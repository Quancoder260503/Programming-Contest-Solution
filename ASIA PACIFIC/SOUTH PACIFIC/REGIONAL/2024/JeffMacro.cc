#include "bits/stdc++.h"

using namespace std;  

#define ll long long 
#define sz(x) int(x.size()) 

const int oo = 1e9; 

string st, en;
int m; 

unordered_map<string, int>dp; 
vector<string>g[26]; 

int match(const string &a, const string &b) { 
 int res = 0; 
 for(int i = 0; i < sz(a); i++) res += a[i] == b[i]; 
 return res; 
}

int memo(const string &s) { 
  if(sz(s) > sz(en)) return -oo; 
  if(sz(s) == sz(en)) return match(s, en); 
  if(dp.count(s)) return dp[s];
  int &res = dp[s]; 
  res = -oo; 
  for(int i = 0; i < sz(s); i++) { 
   for(auto &nx : g[s[i] - 'A']) { 
    string t = s.substr(0, i) + nx + (i + 1 < sz(s) ? s.substr(i + 1) : ""); 
    res = max(res, memo(t)); 
   }
  }
  return res; 
}

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);   
 cin >> st >> en >> m;
 for(int i = 0; i < m; i++) { 
  string c; 
  cin >> c; 
  g[c[0] - 'A'].push_back(c); 
 }
 cout << max(0, memo(st)) << '\n'; 
 return 0; 
}