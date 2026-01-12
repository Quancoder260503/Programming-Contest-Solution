#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <stack> 
#include <numeric> 
#include <set>
#include <queue>
#include <utility>  

using namespace std;

#define sz(x) int(x.size()) 
using ll = long long; 


int main(void) { 
 int n; 
 cin >> n;
 priority_queue<int>pq;
 ll ans = 0; 
 for(int i = 0, x; i < n; i++) { 
  cin >> x; 
  ans += x; 
  pq.push(x); 
  pq.push(x);
  pq.pop();  
 }
 for(int i = 0; i < n; i++) { 
  ans = ans - pq.top(); 
  pq.pop(); 
 }
 cout << ans << '\n'; 
 return 0; 
}

