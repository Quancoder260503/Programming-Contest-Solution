#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

int main() {
 int N, K;
 cin >> N >> K; 
 map<int, int>g; 
 function<int(int)> grundy = [&](int stones) {
  if(K % 2 == 0) { 
    if(stones == 0) return 0; 
    if(stones == 1) return 1; 
    if(stones == 2) return 2; 
    return (stones & 1 ? 0 : 1); 
  } else { 
    if(stones == 0 || stones == 2) return 0; 
    if(stones == 1 || stones == 3) return 1; 
    if(stones == 4) return 2;
    if(stones & 1)  return 0;
    if(g.count(stones)) return g[stones]; 
    return g[stones] = (grundy(stones / 2) == 1 ? 2 : 1); 
  } 
 };
 int ret = 0; 
 for(int i = 0, x; i < N; i++) { 
  cin >> x; 
  ret = ret ^ grundy(x); 
 } 
 cout << (ret ? "Kevin" : "Nicky") << '\n'; 
 return 0; 
}