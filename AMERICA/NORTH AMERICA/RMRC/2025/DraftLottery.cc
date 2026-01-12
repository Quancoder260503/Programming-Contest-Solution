#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxn = 100;

double prob[maxn][maxn][maxn]; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(nullptr); 
 int n, q; 
 cin >> n; 
 cout << fixed << setprecision(10); 
 vector<pair<string, int>> teams(n); 
 unordered_map<string, int> team_index;
 int cnt = 0, sum = 0; 
 for(auto &x : teams) { 
  cin >> x.second >> x.first; 
  team_index[x.first] = cnt++;
  sum += x.second;  
 } 
 for(int i = 0; i < n; i++) { 
  for(int j = 0; j < n; j++) if(i != j) { 
   for(int k = 0; k < n; k++) if(k != i && k != j) {   
      prob[i][j][k] =  (1.0 * teams[i].second / sum) * 
                       (1.0 * teams[j].second / (sum - teams[i].second)) * 
                       (1.0 * teams[k].second / (sum - teams[i].second - teams[j].second)); 
   }
  }
 }
 cin >> q; 
 for(int itr = 0; itr < q; itr++) { 
  string team_name; 
  int rank; 
  cin >> team_name >> rank; 
  double ans = 0;
  int ind = team_index[team_name]; 
  for(int i = 0; i < n; i++) { 
   for(int j = 0; j < n; j++) { 
    ans += prob[ind][i][j] * (1 <= rank) + prob[i][ind][j] * (2 <= rank) + prob[i][j][ind] * (3 <= rank); 
   }
  }
  if(ind < rank) { 
   for(int i = 0; i < ind; i++) { 
    for(int j = 0; j < ind; j++) { 
     for(int k = 0; k < ind; k++) { 
      ans += prob[i][j][k]; 
     }
    }
   } 
  }
  if(ind + 1 < rank) { 
   for(int i = ind + 1; i < n; i++) { 
    for(int j = 0; j < ind; j++) { 
     for(int k = 0; k < ind; k++) {
      ans += prob[i][j][k] + prob[j][i][k] + prob[j][k][i]; 
      //cout << prob[i][j][k] << ' ' << prob[i][k][j] << ' ' << prob[k][i][j] << '\n';   
     }
    } 
   } 
  }
  if(ind + 2 < rank) { 
   for(int i = ind + 1; i < n; i++) { 
    for(int j = ind + 1; j < n; j++) { 
     for(int k = 0; k < ind; k++) { 
      ans += prob[i][j][k] + prob[i][k][j] + prob[k][i][j]; 
     }
    }
   }
  }
  if(ind + 3 < rank) { 
   for(int i = ind + 1; i < n; i++) { 
    for(int j = ind + 1; j < n; j++) { 
     for(int k = ind + 1; k < n; k++) { 
      ans += prob[i][j][k]; 
     }
    }
   }
  }
  cout << ans << '\n'; 
 }
 return 0; 
}