#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 

int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 string S; 
 cin >> S; 
 vector<pair<int, int>>freq; 
 for(int i = 0; i < sz(S); i++) { 
  if(S[i] == 'a' || S[i] == 'b') { 
   int c = 0, ex = 0; 
   while(i + c < sz(S) && S[i + c] != (S[i] == 'a' ? 'b' : 'a')) { 
    if(S[i + c] != 'a' && S[i + c] != 'b') { 
      ex++; 
    } 
    c++;
   }
   //cout << c << " " << ex << '\n'; 
   freq.push_back({S[i] - 'a', c - ex}); 
   i = i + c - 1; 
  }
 } 
 if(sz(freq) == 0) { 
  cout << 0 << '\n'; 
  return 0; 
 } 
 int N = sz(freq); 
 int64_t ret = 1; 
 for(int i = 0; i < N; i++) { 
  if(freq[i].first == 0) ret = ret % MOD * (freq[i].second + 1) % MOD; 
 } 
 cout << ret - 1 << '\n'; 
 return 0; 
}