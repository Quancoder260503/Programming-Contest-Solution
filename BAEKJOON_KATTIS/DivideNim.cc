#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

int main() {
 int N; 
 cin >> N;
 /*
 map<int, int>g; 
 function<int(int)> grundy = [&](int stones) { 
  cerr << stones << '\n'; 
  if(stones == 0) return 0; 
  if(stones == 1) return 1; 
  if(g.count(stones)) return g[stones]; 
  set<int>s; 
  for(int i = 1; i <= stones; i++) { 
   s.insert(grundy(stones - i)); 
   if(i < stones) s.insert(grundy(stones - i) ^ grundy(i)); 
  } 
  int mex = 0; 
  while(s.count(mex)) mex++; 
  return g[stones] = mex; 
 }; 
 */
 int ret = 0; 
 for(int i = 0, x; i < N; i++) { 
  cin >> x; 
  if(x % 4 == 3) { 
   x++; 
  } else if(x % 4 == 0) { 
    x--; 
  } 
  ret = ret ^ x; 
 } 
 cout << (ret ? "koosaga" : "cubelover") << '\n'; 
 return 0; 
}