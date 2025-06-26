#include "bits/stdc++.h"

using namespace std;

const int64_t oo = LLONG_MAX / 1000; 

#define sz(x) int(x.size())

const int LOG = 20; 

int64_t dyn[LOG][(1 << LOG)]; 
int N, T;  
vector<int64_t>d, p, tt, cost; 
vector<vector<int64_t>>dist; 

int64_t memo(int mask, int dst) { 
  int64_t &ret = dyn[dst][mask]; 
  if(ret != -1) return ret;  
  if(mask == (1 << dst)) { 
    if(d[dst] == -1 || (dist[N][dst] + tt[dst] <= d[dst])) { 
      return ret = dist[N][dst] + tt[dst]; 
    }
    else { return ret = oo; }
  } 
  ret = oo; 
  for(int from = 0; from < N; from++) if(from != dst && (mask & (1 << from))) { 
    int64_t cc = memo(mask ^ (1 << dst), from); 
    if(d[dst] == -1 || tt[dst] + dist[from][dst] + cc <= d[dst]) { 
      ret = min(ret, tt[dst] + dist[from][dst] + cc); 
    }
  }
  return ret; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> N >> T;
  d.resize(N); p.resize(N); tt.resize(N); cost.resize((1 << N));  
  dist.resize(N + 2, vector<int64_t>(N + 2)); 
  for(int i = 0; i < N; i++) { 
    cin >> p[i] >> tt[i] >> d[i]; 
  } 
  for(int i = 0; i < N + 2; i++) { 
    for(int j = 0; j < N + 2; j++) { 
       cin >> dist[i][j]; 
    }
  }
  for(int mask = 0; mask < (1 << N); mask++) { 
    for(int i = 0; i < N; i++) if(mask & (1 << i)) { 
       cost[mask] += p[i]; 
    }
  }
  memset(dyn, -1, sizeof(dyn)); 
  int64_t ret = -1; 
  vector<int>loc; 
  for(int i = 0; i < N; i++) { 
    for(int mask = 0; mask < (1 << N); mask++) if(mask & (1 << i)) { 
       int64_t cc = memo(mask, i);  
       if(cc + dist[i][N + 1] <= T) {
         if(ret == cost[mask]) { 
           loc.push_back(mask); 
         }
         else if(ret < cost[mask]) { 
           loc.clear(); 
           loc.push_back(mask); 
           ret = cost[mask]; 
         }
       } 
    }
  }
  if(ret == -1) { 
    cout << 0 << '\n'; 
  }
  else { 
    cout << ret << '\n'; 
    vector<int>cc; 
    for(auto mask : loc) {
      vector<int>Temp; 
      for(int i = 0; i < N; i++) if(mask & (1 << i)) { 
        Temp.push_back(i + 1); 
      }
      if(sz(cc) == 0) { cc = Temp; }
      else { cc = min(cc, Temp); }
    }
    for(auto &x : cc) { cout << x << " "; }
    cout << '\n'; 
  }
  return 0; 
}

