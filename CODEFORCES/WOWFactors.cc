#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
 string s; 
 cin >> s; 
 int N = sz(s); 
 vector<int>prefix(N), suffix(N); 
 for(int i = 1; i < N; i++) { 
  prefix[i] = prefix[i - 1] + (s[i] == 'v' && s[i - 1] == 'v'); 
 }
 for(int i = N - 2; i >= 0; i--) { 
  suffix[i] += suffix[i + 1] + (s[i] == 'v' && s[i + 1] == 'v'); 
 }
 int64_t ans = 0; 
 for(int i = 0; i < N; i++) { 
  if(s[i] == 'o') { 
    ans += 1LL * prefix[i] * suffix[i];  
  }  
 }
 cout << ans << '\n'; 
 return 0; 
}