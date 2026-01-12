#include <vector> 
#include <iostream> 

using namespace std; 

int main(void) { 
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0); 
 int n, k, T; 
 for(cin >> T; T--; ) {   
  cin >> n >> k;
  if(n == 2) { 
   if(k % 2 == 0) cout << 1 << " " << 2 << '\n'; 
   else cout << 2 << " " << 1 << '\n'; 
   continue;
  }

  if(n <= k) { 
   for(int i = 0; i < n; i++) cout << n - i << ' '; 
   cout << '\n'; 
   continue;
  }
  for(int i = 0; i < k; i++) { 
   cout << n - i << " "; 
  }
  for(int i = 1; i <= n - k; i++) cout << i << " "; 
  cout << '\n'; 
 } 
 return 0; 
}