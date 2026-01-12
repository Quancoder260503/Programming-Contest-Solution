#include <iostream> 
#include <vector> 
#include <algorithm> 

using namespace std; 

using ll = long long; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n, m; 
 cin >> n >> m; 
 vector<int>a(n); 
 vector<int>b(m); 
 for(int i = 0; i < n; i++) { 
  cin >> a[i];    
 }
 for(int i = 0; i < m; i++) { 
  cin >> b[i]; 
  b[i]--; 
 }
 ll ans = LLONG_MAX; 
 for(int i = 0; i < n; i++) { 
  vector<int>c(n); 
  for(int j = 0; j < n; j++) { 
   c[j] = a[(i + j) % n]; 
  }   
  int ok = true; 
  for(int j = 1; j < m; j++) { 
   ok = ok & (c[b[j]] > c[b[j - 1]]); 
  }
  if(ok) { 
   ll sum = 0; 
   for(int j = 0; j < m; j++) { 
    sum += c[b[j]];  
   }
   ans = min(ans, sum); 
  }
 }
 cout << (ans == LLONG_MAX ? -1 : ans) << '\n'; 
 return 0; 
}