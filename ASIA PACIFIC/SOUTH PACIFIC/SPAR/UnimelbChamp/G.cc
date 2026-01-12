#include <iostream> 
#include <unordered_map> 
#include <vector> 

using namespace std; 

using ll = long long; 

void solve() {
 int n; 
 cin >> n;  
 unordered_map<ll, int>mp; 
 for(int i = 0; i < n; i++) {
  ll x; 
  cin >> x;  
  mp[x]++; 
 }
 for(const auto &[u, v] : mp) { 
  if(v == 4) { 
   cout << u << '\n'; 
   return; 
  }
 }
 cout << -1 << '\n'; 
 return; 
}

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int C; 
 cin >> C; 
 while(C--) { 
  solve(); 
 }
 return 0; 
}
