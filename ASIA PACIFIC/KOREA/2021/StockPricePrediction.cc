#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxn = 2e6; 
int bit[maxn], cnt[maxn]; 

void update(int x, int val) {
 cnt[x] += val;  
 for(x++; x < maxn; x += x & (-x)) { 
  bit[x] += val; 
 }
 return; 
}

pair<int, int> query(int x) { 
 int ret = 0, c = cnt[x] > 0;  
 for(x++; x > 0; x -= x & (-x)) { 
  ret += bit[x]; 
 }
 return {ret, c}; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N, M; 
  cin >> N >> M; 
  vector<int>a(N), b(M);  
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  }
  for(int i = 0; i < M; i++) { 
   cin >> b[i]; 
  }
  vector<int>coord_a(a.begin(), a.end()), coord_b(b.begin(), b.end()); 
  sort(coord_a.begin(), coord_a.end()); 
  sort(coord_b.begin(), coord_b.end()); 
  coord_a.erase(unique(coord_a.begin(), coord_a.end()), coord_a.end()); 
  coord_b.erase(unique(coord_b.begin(), coord_b.end()), coord_b.end()); 
  for(int i = 0; i < N; i++) { 
    a[i] = lower_bound(coord_a.begin(), coord_a.end(), a[i]) - coord_a.begin() + 1; 
  }
  for(int i = 0; i < M; i++) { 
    b[i] = lower_bound(coord_b.begin(), coord_b.end(), b[i]) - coord_b.begin() + 1; 
  }
  vector<pair<int, int>>val(N); 
  for(int i = 0; i < N; i++) { 
   val[i] = query(a[i]); 
   update(a[i], 1); 
  }
  memset(bit, 0, sizeof(bit)); 
  memset(cnt, 0, sizeof(cnt));

  vector<int>failure(N, -1); 
  for(int i = 1, curr = -1, l = 1; i < N; i++) { 
   while(curr != -1 && val[curr + 1] != query(a[i])) { 
    curr = failure[curr]; 
    while(l < i - curr - 1) { 
     update(a[l++], -1); 
    }
   }
   if(val[curr + 1] == query(a[i])) ++curr; 
   failure[i] = curr; 
   update(a[i], 1); 
  }
  memset(bit, 0, sizeof(bit)); 
  memset(cnt, 0, sizeof(cnt)); 

  val.push_back({-1, -1}); 
  vector<int>ret; 
  for(int i = 0, curr = -1, l = 0; i < M; i++) { 
   while(curr != -1 && val[curr + 1] != query(b[i])) { 
    curr = failure[curr]; 
    while(l < i - curr - 1) { 
     update(b[l++], -1); 
    }
   }
   if(val[curr + 1] == query(b[i])) ++curr; 
   if(curr == N - 1) { 
    ret.push_back(i - N + 2); 
   }
   update(b[i], 1); 
  }
  if(sz(ret) == 0) cout << 0 << '\n'; 
  else { 
   for(auto &x : ret) cout << x << " "; 
   cout << '\n'; 
  } 
  return 0; 
}
