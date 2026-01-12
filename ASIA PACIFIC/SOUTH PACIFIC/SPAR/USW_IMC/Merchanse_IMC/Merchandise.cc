#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <stack> 
#include <numeric> 
#include <set> 

using namespace std;

#define sz(x) int(x.size()) 
using ll = long long; 


int main(void) { 
 int C, n; 
 cin >> C >> n; 
 vector<pair<int, int>>c(n); 
 for(int i = 0; i < n; i++) { 
  cin >> c[i].first >> c[i].second; 
 }
 sort(c.begin(), c.end()); 
 multiset<int>ms; 
 int cnt = 0; 
 ll ret = 0; 
 for(int i = 0; i < n; i++) { 
  int u = c[i].first, v = c[i].second; 
  while(ms.size() < u) ms.insert(0); 
  while(cnt < v) { 
   int c = *ms.begin(); 
   ms.erase(ms.find(c)); 
   ret += 2LL * c + 1;
   ms.insert(c + 1); 
   cnt++;  
  }
 }
 cout << ret << '\n'; 
 return 0; 
}

