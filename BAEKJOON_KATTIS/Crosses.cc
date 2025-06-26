#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

int main() {
 int N; 
 cin >> N;
 map<int, int>g; 
 function<int(int)> grundy = [&](int stones) { 
  if(stones <= 0) return 0; 
  if(stones <= 3) return 1; 
  if(g.count(stones)) return g[stones]; 
  set<int>s; 
  for(int j = 1; j <= (stones + 1) / 2; j++) { 
   s.insert(grundy(stones - j - 2) ^ grundy(j - 3)); 
  }
  int mex = 0; 
  while(s.count(mex)) mex++; 
  return g[stones] = mex; 
 }; 
 cout << (grundy(N) ? 1 : 2) << '\n'; 
 return 0; 
}