#include "bits/stdc++.h"

using namespace std; 

int main(void) {
 int n, m, e;  
 cin >> n; 
 vector<int>a(n); 
 for(auto &x : a) cin >> x; 
 cin >> m >> e; 
 vector<int>belt(m + 1), ans(m); 
 int ptr_i = 0, ptr_j = 0; 
 for(int t, p; e--; ) { 
   cin >> t >> p;
   for(; ptr_j < t; ptr_j++) { 
    if(!belt[0]) { 
     belt[0] = a[ptr_i % n]; 
     ptr_i++; 
    }
    rotate(belt.begin(), belt.end() - 1, belt.end()); 
   } ans[p - 1] += belt[p]; 
    belt[p] = 0;   
 }
 for(auto &x : ans) cout << x << '\n'; 
 return 0; 
}