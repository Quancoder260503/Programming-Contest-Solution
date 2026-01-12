#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
int main(void) {
  int N, K; 
  cin >> N; 
  vector<tuple<int, char, int>>arr; 
  for(int i = 0; i < N; i++) { 
   int pos, dist; 
   char dir; 
   cin >> pos >> dir >> dist; 
   arr.push_back({pos, dir, dist}); 
  }
  int st; 
  cin >> st; 
  while(true) { 
   int found = false; 
   for(auto [pos, dir, dist] : arr) {
    if(pos == st) { 
     st += (dir == 'L' ? -1 : 1) * dist; 
     found = true; 
     break; 
    } 
   }
   if(!found) { 
    break; 
   }
  }
  cout << st << '\n'; 
  return 0; 
}