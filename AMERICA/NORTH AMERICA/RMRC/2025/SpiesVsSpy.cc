#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(nullptr); 
 int n, q; 
 cin >> n >> q;
 unordered_map<int, set<pair<int, int>>>row, col;
 vector<int>marked(n);
 vector<pair<int, int>>coord(n);  
 for(int i = 0; i < n; i++) { 
  cin >> coord[i].first >> coord[i].second; 
  row[coord[i].second].insert({coord[i].first, i}); 
  col[coord[i].first].insert({coord[i].second, i}); 
 } 
 for(int i = 0; i < q; i++) { 
  int pos; 
  char dir; 
  cin >> pos >> dir; 
  --pos; 
  if(marked[pos]) { 
   cout << "ignore\n"; 
   continue; 
  }
  vector<int>ans; 
  if(dir == 'N') { 
   auto it = col[coord[pos].first].upper_bound({coord[pos].second, pos});
   vector<pair<int, int>>to_erase;  
   while(it != col[coord[pos].first].end()) { 
    int idx = it->second;
    ans.push_back(idx);  
    marked[idx] = 1;
    row[coord[idx].second].erase({coord[idx].first, idx}); 
    to_erase.push_back(*it); 
    it++;  
   }
   for(auto &x : to_erase) { 
    col[coord[pos].first].erase(x); 
   }

  } else if(dir == 'S') { 
    auto curr_it = col[coord[pos].first].lower_bound({coord[pos].second, pos}); 
    auto it = col[coord[pos].first].begin();  
    vector<pair<int, int>>to_erase; 
    while(it != curr_it) { 
     int idx = it->second;
     ans.push_back(idx);  
     to_erase.push_back(*it); 
     marked[idx] = 1; 
     row[coord[idx].second].erase({coord[idx].first, idx}); 
     it++; 
    }
    for(auto &x : to_erase) { 
     col[coord[pos].first].erase(x); 
    }
    reverse(ans.begin(), ans.end()); 

  } else if(dir == 'E') { 
   auto it = row[coord[pos].second].upper_bound({coord[pos].first, pos});
   vector<pair<int, int>>to_erase;  
   while(it != row[coord[pos].second].end()) { 
    int idx = it->second;
    ans.push_back(idx);  
    marked[idx] = 1;
    col[coord[idx].first].erase({coord[idx].second, idx}); 
    to_erase.push_back(*it); 
    it++;  
   }
   for(auto &x : to_erase) { 
    row[coord[pos].second].erase(x); 
   }
  }
  else { 
    auto curr_it = row[coord[pos].second].lower_bound({coord[pos].first, pos}); 
    auto it = row[coord[pos].second].begin(); 
    vector<pair<int, int>>to_erase; 
    while(it != curr_it) { 
     int idx = it->second;
     ans.push_back(idx);  
     to_erase.push_back(*it); 
     marked[idx] = 1; 
     col[coord[idx].first].erase({coord[idx].second, idx}); 
     it++; 
    }
    for(auto &x : to_erase) { 
     row[coord[pos].second].erase(x); 
    }
    reverse(ans.begin(), ans.end()); 
  }
  cout << sz(ans) << " "; 
  for(auto &x : ans) cout << x + 1 << " "; 
  cout << '\n'; 
 }
 return 0; 
}

