#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M, X, Y; 
  cin >> N >> M >> X >> Y;
  vector<int>a(N), b(M);
  for(int i = 0; i < N; i++) { 
   cin >> a[i];  
  } 
  for(int i = 0; i < M; i++) { 
   cin >> b[i]; 
  }
  sort(a.begin(), a.end()); 
  sort(b.begin(), b.end()); 

  auto check = [&](int num_arts) { 
   priority_queue<array<int, 2>>pq; 
   for(int i = 0; i < num_arts; i++) { 
    pq.push({a[i], Y}); 
   }
   vector<int>vis(M); 
   for(int i = M - 1; i >= 0; i--) { 
    if(sz(pq) == 0) break; 
    auto [height, num_slot] = pq.top();
    if(height < b[i]) { 
     continue; 
    }
    pq.pop();  
    vis[i] = true; 
    if(num_slot > 1) { 
     pq.push({height, num_slot - 1}); 
    }
   }
   vector<int>remain; 
   for(int i = 0; i < M; i++) { 
    if(vis[i]) continue; 
    remain.push_back(i); 
   }
   while(sz(pq)) pq.pop(); 
   for(int i = num_arts; i < N; i++) { 
    pq.push({a[i], X}); 
   }
   for(int i = sz(remain) - 1; i >= 0; i--) { 
    if(sz(pq) == 0) return false; 
    auto [height, num_slot] = pq.top(); 
    pq.pop(); 
    if(height < b[remain[i]]) return false; 
    vis[remain[i]] = true; 
    if(num_slot > 1) { 
      pq.push({height, num_slot - 1}); 
    }
   }
   for(int i = 0; i < M; i++) { 
    if(!vis[i]) return false; 
   }
   return true; 
  }; 
  int lo = -1, hi = N; 
  while(lo < hi) { 
   int mid = (lo + hi + 1) / 2; 
   if(check(mid)) lo = mid; 
   else hi = mid - 1; 
  }
  if(lo == -1) cout << "impossible" << '\n'; 
  else cout << lo << '\n'; 
  return 0; 
}
