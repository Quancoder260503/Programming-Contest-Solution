#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

using namespace std; 

int main(void) {
 int n, m; 
 cin >> n >> m; 
 vector<int>p(n + 1); 
 iota(p.begin(), p.end(), 0); 
 for(int i = 0; i < m; i++) { 
  string u, v; 
  cin >> u >> v; 
  int a = stoi(u.substr(1)), b = stoi(v.substr(1));
  int pa, pb;  
  for(int j = 1; j <= n; j++) { 
   if(p[j] == a) pa = j; 
   if(p[j] == b) pb = j; 
  }
  if(pa > pb) { 
   for(int i = pb; i < pa; i++) { 
    p[i] = p[i + 1]; 
   }
   p[pa] = b; 
  }
 }    
 for(int i = 1; i <= n; i++) { 
  cout << "T" << p[i] << ' '; 
 }
 cout << '\n'; 
 return 0; 
} 
