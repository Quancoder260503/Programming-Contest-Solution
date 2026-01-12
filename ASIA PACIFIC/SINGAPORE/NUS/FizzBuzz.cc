#include "bits/stdc++.h"

using namespace std;

#define ll long long

const string quote = "F_in_Finals_stands_for_Fizz_Buzz!"; 
int64_t pw3[40]; 

char rec(ll pos, int ind) {   
 if(ind == 0) return 'F'; 
 int64_t len = pw3[ind - 1] * 16 - 15; 

 if(pos < len) return rec(pos, ind - 1); 
 pos = pos - len; 
 if(pos < 4) { 
  return quote[1 + pos];   
 }
 pos = pos - 4;

 if(pos < len) return rec(pos, ind - 1); 
 pos = pos - len; 
 if(pos < 17) { 
  return quote[6 + pos]; 
 }
 pos = pos - 17; 

 if(pos < len) return rec(pos, ind - 1); 
 pos = pos - len; 

 return pos < 9 ? quote[24 + pos] : '?'; 
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0); 
  pw3[0] = 1; 
  for(int i = 1; i < 39; i++) { 
   pw3[i] = pw3[i - 1] * 3; 
  }
  int T; 
  ll n, m; 
  for(cin >> T; T--; ) { 
   cin >> n >> m; 
   cout << rec(n - 1, min(36LL, m + 1)); 
  }
  cout << '\n'; 
  return 0; 
}