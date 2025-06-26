#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

void solve() { 
 int N; 
 cin >> N; 
 vector<int>a(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 int g = a[0]; 
 for(int i = 0; i < N; i++) { 
  g = gcd(g, a[i]); 
 }
 for(int i = 0; i < N; i++) { 
  a[i] = a[i] / g; 
 }
 int curr = *min_element(a.begin(), a.end());
 int64_t ret = curr; 
 if(curr == 1) { 
  ret += (N - 1); 
 } else { 
  for(int c = 0; c < 20; c++) { 
   int opt = int(1e9); 
   for(int i = 0; i < N; i++) { 
    opt = min(opt, gcd(curr, a[i])); 
   }
   curr = opt;
   ret += curr;
   if(curr == 1) { 
    ret += (N - c - 2); 
    break; 
   }
  }
 } 
 cout << ret * g << '\n';  
 // consider only distinc valuve
 return; 
}

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);  
 int T; 
 for(cin >> T; T--; ) { solve(); }
 return 0; 
}

/** 
 Solve the problem where gcd(a[1], a[2], ... a[n]) = 1
 first sort the array
  // DP ON DAG ??? 


  2 4 6 8 = [1, 2, 3, 4] 
**/ 