#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int64_t oo = 1e12; 
const int maxn = 3e5 + 10; 

int occ[maxn];
vector<int64_t>cost[maxn];  

int64_t bit[maxn], cnt[maxn]; 

void update(int x, int val) { 
 for(x++; x < maxn; x += x & (-x)) { 
  bit[x] += val; 
  cnt[x]++;    
 }
 return; 
}
int queryCnt(int x) { 
 int ret = 0; 
 for(x++; x > 0; x -= x & (-x)) { 
  ret += cnt[x]; 
 }   
 return ret; 
}
int queryCnt(int x, int y) { 
  return queryCnt(y) - queryCnt(x - 1); 
}

int64_t queryVal(int x) { 
 int64_t ret = 0; 
 for(x++; x > 0; x -= x & (-x)) { 
  ret += bit[x]; 
 }   
 return ret; 
}

int64_t queryVal(int x, int y) { 
  return queryVal(y) - queryVal(x - 1); 
}


int main(void) {
  ios_base::sync_with_stdio(0); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<int>a(N), b(N); 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
   occ[a[i]]++; 
  }
  for(int i = 0; i < N; i++) { 
   cin >> b[i]; 
   cost[a[i]].push_back(b[i]); 
  }
  sort(a.begin(), a.end()); 
  a.erase(unique(a.begin(), a.end()), a.end()); 
  int n = a.size(); 
  int64_t total = 0; 
  for(int j = 0; j < n; j++) { 
   int i = a[j]; 
   sort(cost[i].begin(), cost[i].end()); 
   for(int j = 1; j < cost[i].size(); j++) { 
    cost[i][j] += cost[i][j - 1]; 
   }
   total += cost[i].back(); 
  }
  
  int64_t ret = oo;  
  int total_num = 0; 
  for(int i = 0; i < n; i++) { 
   int64_t extra = 0;
   int need = total_num - occ[a[i]]; 
   if(need >= 0) { 
    need++; 
    int lo = 0, hi = maxn;
    while(lo < hi) { 
     int mid = (lo + hi) / 2; 
     if(queryCnt(mid) >= need) { 
      hi = mid;   
     } else { 
      lo = mid + 1; 
     }
    }
    extra = queryVal(lo) - 1LL * lo * (queryCnt(lo) - need); 
   // cout << lo << " " << queryCnt(lo) - need << '\n'; 
   } 
   total -= cost[a[i]].back(); 
   ret = min(ret, total + extra); 
   total_num += occ[a[i]]; 
   for(int j = 0; j < cost[a[i]].size(); j++) { 
    int c = cost[a[i]][j] - (j ? cost[a[i]][j - 1] : 0); 
    update(c, c); 
   }
  // cout << extra << " " << total << " " << need << " " << extra << '\n'; 
  }
  cout << ret << '\n'; 
  return 0; 
}
