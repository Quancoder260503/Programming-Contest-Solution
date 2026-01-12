#include "bits/stdc++.h"

using namespace std; 

int main(void) {
 int n; 
 cin >> n;
 unordered_map<string, string>who;  
 who["fishing"] = "alice"; 
 who["golf"] = "bob";
 who["hockey"] = "charlie"; 
 for(int i = 0; i < n; i++) { 
  string a, m, b; 
  cin >> a; 
  for(int j = 0; j < 3; j++) cin >> m; 
  cin >> b; 
  if(who[b] != a) cout << a << " borrows " << b << " from " << who[b] << '\n';
  else            cout << a << " already has " << b << '\n';
  who[b] = a; 
 }
 return 0; 
}