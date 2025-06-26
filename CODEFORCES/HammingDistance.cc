#include <bits/stdc++.h>

using namespace std; 

#define sz(x) int(x.size())

int main() {
 string a, b; 
 cin >> a >> b; 
 vector<int>zeros(sz(b)), ones(sz(b)); 
 for(int i = 0; i < sz(b); i++) { 
  zeros[i] = (i ? zeros[i - 1] : 0) + (b[i] == '0'); 
  ones[i]  = (i ? ones[i - 1]  : 0) + (b[i] == '1'); 
 } 
 int64_t ret = 0; 
 for(int i = 0; i < sz(a); i++) {
  if(a[i] == '0') {
   ret += ones[min(sz(b) - 1, sz(b) - sz(a) + i)] - (i ? ones[i - 1] : 0);
  } else { 
   ret += zeros[min(sz(b) - 1, sz(b) - sz(a) + i)] - (i ? zeros[i - 1] : 0); 
  } 
 }
 cout << ret << '\n'; 
 return 0;
}