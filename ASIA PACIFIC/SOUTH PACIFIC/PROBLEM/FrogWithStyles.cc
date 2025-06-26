#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const double oo = 1e50; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N;
  double D;
  while(cin >> N >> D && N) { 
    vector<pair<double, double>>pts(N); 
    for(int i = 0; i < N; i++) { 
      cin >> pts[i].first >> pts[i].second; 
    }
    auto getDist = [&](int i, int j) { 
      return hypot(pts[i].first - pts[j].first, pts[i].second - pts[j].second); 
    }; 
    using T = tuple<double, int, int>;
    priority_queue<T>pq; 
    vector<vector<double>>best(N, vector<double>(N + 1, -oo));
    best[0][0] = oo; 
    pq.push({oo, 0, 0}); 
    while(sz(pq)) { 
      auto [d, u, hops] = pq.top(); 
      pq.pop(); 
      if(hops == N) continue; 
      for(int i = 0; i < N; i++) { 
        double dist = getDist(u, i); 
        if(dist > D) continue; 
        if(best[i][hops + 1] < min(best[u][hops], dist)) { 
          best[i][hops + 1] = min(best[u][hops], dist); 
          pq.push({best[i][hops + 1], i, hops + 1});   
        } 
      }
    }
    for(int hops = 0; hops <= N; hops++) { 
      if(best[1][hops] != -oo) { 
        cout << hops << " " << fixed << setprecision(1) << best[1][hops] << '\n'; 
        goto done; 
      }
    }
  done:; 
  }
  return 0; 
}

