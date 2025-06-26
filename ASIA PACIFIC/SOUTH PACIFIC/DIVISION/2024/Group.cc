#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

int main() {
  vector<string>word(9); 
  for(int i = 0; i < 9; i++) { 
   cin >> word[i]; 
  } 
  map<pair<string, string>, bool>g; 
  int N; 
  cin >> N; 
  string U, V; 
  for(int i = 0; i < N; i++) { 
    cin >> U >> V;
   // cout << U << " " << V << '\n'; 
    g[{U, V}] = g[{V, U}] = true; 
  } 
  for(int mask = 0; mask < (1 << 9); mask++) { 
   if(__builtin_popcount(mask) == 3) { 
    vector<string>gg, rem; 
    for(int i = 0; i < 9; i++) { 
     if(mask & (1 << i)) { 
      gg.push_back(word[i]); 
     } 
     else { 
      rem.push_back(word[i]); 
     } 
    }
    for(int mask1 = 0; mask1 < (1 << 6); mask1++) { 
     if(__builtin_popcount(mask1) == 3) { 
      vector<string>group1, group2; 
      for(int i = 0; i < 6; i++) {
       if(mask1 & (1 << i)) { 
        group1.push_back(rem[i]); 
       } 
       else { 
        group2.push_back(rem[i]); 
       } 
      }
      vector<vector<string>>group;
      group.push_back(gg); 
      group.push_back(group1); 
      group.push_back(group2);
      for(auto &x : group) {
       int flag = true; 
       for(int i = 0; i < sz(x); i++) { 
        for(int j = i + 1; j < sz(x); j++) { 
         if(!g.count({x[i], x[j]})) { 
          flag = false; 
         } 
        } 
       }
       if(!flag) goto done; 
      }
      cout << "Possible\n"; 
      for(auto &x : group) { 
       for(auto &y : x) { 
        cout << y << " "; 
       } 
       cout << '\n'; 
      }
      exit(0); 
    done:; 
     } 
    } 
   } 
  } 
  cout << "Impossible\n"; 
  return 0;
}

 
 