#include <bits/stdc++.h>

using namespace std; 

#define sz(x) int(x.size())

const int LOG = 31; 

int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, K; 
 cin >> N >> K; 
 multiset<int>ms; 
 for(int i = 0; i < LOG; i++) { 
  if(N & (1 << i)) { 
   ms.insert(i); 
  } 
 } 
 if(sz(ms) > K) {
  cout << "NO\n";
 }
 else { 
  while(sz(ms) < K) { 
   auto it = prev(ms.end());
   int v = *it; 
   if(v == 0) { 
    cout << "NO\n"; 
    return 0; 
   } 
   ms.erase(it); 
   ms.insert(v - 1); 
   ms.insert(v - 1); 
  } 
  cout << "YES\n"; 
  for(auto &x : ms) cout << (int) pow(2, x) << " "; 
 } 
 return 0;
}