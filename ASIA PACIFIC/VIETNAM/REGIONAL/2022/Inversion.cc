#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

int main(void) {
  int N; 
  cin >> N; 
  vector<int>inv(N); 
  auto ask = [&](int i, int j) { 
   cout << "? " << " " << i << " " << j << '\n'; 
   int ret; 
   cin >> ret; 
   return ret; 
  }; 
  auto answer = [&](vector<int>ans) { 
   cout << "! "; 
   for(auto &x : ans) { 
    cout << x + 1 << " "; 
   }
   cout << '\n'; 
  }; 
  for(int i = 0; i < N; i++) { 
   inv[i] = ask(1, i + 1); 
  }
  vector<int>ans{0}; 
  int first = 0; 
  for(int i = 1; i < N; i++) { 
   int &c = ans.emplace_back(0); 
   int inv_change = inv[i] - inv[0];
   for(c = 0; c < sz(ans) - 1; c++) {
    int num_inv = inv_change - first; 
    num_inv -= c; 
    num_inv += sz(ans) - 1 - c; 
    if(num_inv == 0) break; 
   }
   for(int j = 0; j < sz(ans) - 1; j++) { 
    ans[j] += ans[j] >= c; 
   }
   first += (c > ans[0] ? 1 : -1);  
  }
  answer(ans); 
  return 0; 
}

