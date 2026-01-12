#include <vector>
#include <iostream>
#include <algorithm> 
#include <functional>
#include <numeric> 

using namespace std; 

#define ll long long 

int main(void) { 
  int n; 
  cin >> n;
  vector<int>a(n); 
  for(int i = 0; i < n; i++) { 
   cin >> a[i];
  }
  int g = a[0]; 
  vector<int>ga(n), gb(n); 
  for(int i = 0; i < n; i++) {
   g = gcd(g, a[i]);  
   ga[i] = g; 
  }
  g = a.back(); 
  ll  ret = 0; 
  for(int i = n - 1; i >= 0; i--) { 
   g = gcd(g, a[i]); 
   gb[i] = g; 
  }
  for(int i = 1; i < n - 1; i++) { 
   ret += min(ga[i], gb[i]);   
  } 
  ret += g; 
  cout << ret << '\n'; 
  return 0; 
}

// Think about the monoticity of gcd value 