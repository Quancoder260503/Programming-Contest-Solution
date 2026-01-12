#include "bits/stdc++.h"

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    int total_matches = (1 << N) - 1;
    vector<int> verdict(total_matches, 1); 

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v; 

        int level = 0;
        for(int j = N - 1; j >= 0; j--) { 
         if((u >> j & 1) > 0 && (v >> j & 1) == 0) { 
          level = j; 
          break;   
         }
         if((v >> j & 1) > 0 && (u >> j & 1) == 0) { 
          level = j; 
          break; 
         }
        }
     //   cout << level << '\n'; 
        int sum = 0; 
        for (int k = 0; k <= level; k++) {
            int node_index_u = sum + (u / (1 << (k + 1))); 
            verdict[node_index_u] = 0;
            int node_index_v = sum + (v / (1 << (k + 1)));
            verdict[node_index_v] = 0; 
          // cout << node_index_u << " " << node_index_v << " " << level << '\n'; 
            sum += (1 << (N - k - 1)); 
        }
    }

    int cnt = 0;
    for (int i = 0; i < verdict.size(); i++) cnt += verdict[i];
    cout << cnt << '\n';

    return 0;
}
