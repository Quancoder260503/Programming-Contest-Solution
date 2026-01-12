#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int maxn = 5e5 + 2; 
int occ[maxn]; 

int main(void) {
  ios_base::sync_with_stdio(0); 
  cin.tie(0); 
  cout.tie(0); 
  int T; 
  for(cin >> T; T--; ) { 
   int n;  
   cin >> n; 
   vector<int>a(n); 
   for(int i = 0; i < n; i++) { 
    cin >> a[i]; 
    occ[a[i]]++; 
   }
   cout << occ[0] << " "; 
   priority_queue<int>pq;
   for(int i = 0; i < occ[0] - 1; i++) { 
    pq.push(0); 
   } 
   int64_t mex = (occ[0] > 0), ret = 0; 
   for(int i = 1; i <= n; i++) { 
   // int ret = 0; 
    while(pq.size() && mex < i) { 
     int u = pq.top(); 
     pq.pop(); 
     if(mex < u) break; 
     ret += mex - u; 
     mex++; 
    } 
    if(mex < i) { 
     cout << -1 << " "; 
    } else { 
     cout << ret + occ[i] << " "; 
    }
    mex += (mex == i && occ[i] > 0); 
    for(int j = 0; j < occ[i] - 1; j++) { 
     pq.push(i); 
    }
   }
   cout << '\n'; 
   for(int i = 0; i < n; i++) { 
    occ[a[i]]--; 
   }
  }
  return 0; 
}
