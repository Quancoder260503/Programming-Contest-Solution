#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define ctoi(x) x - 'a' 

const int maxn = 1000002; 
int vis[maxn]; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);  
 int n; 
 cin >> n; 
 int max_val = 0; 
 for(int i = 0, x; i < n; i++) {
  cin >> x;  
  max_val = max(max_val, x); 
  vis[x] = 1; 
 }
 int ans = 0; 
 for(int i = 1; i < maxn; i++) { 
  int g = -1; 
  for(int j = i; j < maxn; j += i) { 
   if(vis[j]) { 
    if(g == -1) g = j; 
    else g = gcd(g, j); 
   }
  }
  if(g == i) ans++; 
 }
 cout << ans - n << '\n'; 
 return 0; 
}