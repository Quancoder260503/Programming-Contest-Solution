#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
const int LOG = 17;
const int maxn = 1e5 + 20; 
vector<int>g[maxn], hh[maxn]; 
int in[maxn], out[maxn], height[maxn], par[maxn], N, Q, timer = 0; 
int64_t down[maxn][LOG]; 

struct Fenwick { 
  vector<int64_t>bit; 
  int n; 
  Fenwick(int N) { 
   n = N; 
   bit.resize(N); 
  }  
  void update(int pos, int64_t v) { 
   for(pos++; pos < n; pos += pos & -pos) { 
    bit[pos] += v; 
   }
   return; 
  }
  int64_t sum(int pos) { 
   int64_t ans = 0; 
   for(pos++; pos > 0; pos -= pos & -pos) { 
    ans += bit[pos]; 
   }
   return ans; 
  }
  int64_t query(int L, int R) { 
   return sum(R) - sum(L - 1); 
  }
}; 

Fenwick fenwick_1(maxn), fenwick_2(maxn), fenwick_3(maxn); 

void dfs(int u, int p, int h) { 
 height[u] = h; 
 in[u] = ++timer; 
 hh[height[u]].push_back(in[u]); 
 for(auto v : g[u]) { 
  if(v == p) continue; 
  dfs(v, u, h + 1); 
 }
 out[u] = timer;
 return; 
}

void update_one(int u, int val) { 
 fenwick_1.update(in[u], 1LL * val * (out[u] - in[u] + 1)); 
 fenwick_2.update(in[u] + 1,  val); 
 fenwick_2.update(out[u] + 1, -val); 
 return; 
}

vector<int>fetch(int u) { 
  vector<int>ret; 
  for(int i = 0; i < LOG; i++) { 
   int depth = height[u] + i; 
   int posL = lower_bound(hh[depth].begin(), hh[depth].end(), in[u])  - hh[depth].begin();
   int posR = upper_bound(hh[depth].begin(), hh[depth].end(), out[u]) - hh[depth].begin();
   ret.push_back(posR - posL); 
  }
  return ret; 
}

void update_K(int u, int y, int val) { 
 int h = height[u]; 
 int64_t sum = 0; 
 vector<int>cc = fetch(u); 
 for(int i = 0; i < LOG; i++) { 
  down[u][i] += y; 
  sum += 1LL * y * cc[i]; 
  y = y / val; 
 }
 fenwick_3.update(in[u], sum); 
 return; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  memset(down, 0, sizeof(down)); 
  cin >> N >> Q;
  par[0] = -1; 
  for(int i = 1, x; i < N; i++) { 
   cin >> par[i]; 
   g[--par[i]].push_back(i); 
  }
  dfs(0, -1, 0); 
  for(int i = 0, type, x, y, val; i < Q; i++) { 
   cin >> type; 
   if(type == 2) { 
    cin >> x; 
    --x; 
    int64_t ans = 0; 
    
    { 
     ans += fenwick_1.query(in[x], out[x]); 
     ans += 1LL * fenwick_2.query(1, in[x]) * (out[x] - in[x] + 1); 
    }
    { 
      ans += fenwick_3.query(in[x], out[x]); 
      vector<int>cc = fetch(x); 
      for(int j = par[x], d = 1; d < LOG && j >= 0; d++, j = par[j]) { 
        for(int p = 0; p + d < LOG; p++) { 
        // cout << ans << " " << j << " " << d + p << " " << down[j][d + p] << '\n'; 
         ans += 1LL * down[j][d + p] * cc[p]; 
        } 
      } 
    }

    cout << ans << '\n'; 
   } else { 
    cin >> x >> y >> val; 
    --x; 
    if(val == 1) update_one(x, y); 
    else update_K(x, y, val); 
   }
  }
  return 0; 
}