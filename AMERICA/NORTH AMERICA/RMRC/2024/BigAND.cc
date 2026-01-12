#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, L, D; 
 cin >> N >> D >> L; 
 priority_queue<int64_t, vector<int64_t>, greater<int64_t>>pq; 
 for(int i = 0, x; i < N; i++) { 
  cin >> x; 
  pq.push(x); 
 }
 int64_t ret = 0; 
 while(sz(pq) > 1) { 
  int64_t a = pq.top(); 
  pq.pop(); 
  int64_t b = pq.top(); 
  pq.pop(); 
  pq.push(max(a, b) + D);
 }
 ret += L + pq.top(); 
 cout << ret << '\n'; 
 return 0; 
}