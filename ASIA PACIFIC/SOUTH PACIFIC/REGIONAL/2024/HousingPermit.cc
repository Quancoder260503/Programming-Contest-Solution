#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxn = 2e5 + 10; 
int R, C, nH, nV; 
vector<int>h[maxn], v[maxn];  

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 cin >> R >> C;
 if(R < C) { 
  cin >> nH; 
  for(int i = 0, r, c; i < nH; i++) { 
   cin >> r >> c; 
   h[r].push_back(c); 
  }
  cin >> nV; 
  for(int i = 0, r, c; i < nV; i++) { 
   cin >> r >> c; 
   v[r].push_back(c); 
  }
  for(int i = 0; i < maxn; i++) { 
   sort(h[i].begin(), h[i].end()); 
   sort(v[i].begin(), v[i].end()); 
  }     
  pair<int, int>res = {0, 0}; 
  for(int r = 1; r <= R; r++) { 
   for(int c = 1; c <= C; c++) { 
    // The square top left is (r, c) 
    int posH = lower_bound(h[r].begin(), h[r].end(), c) - h[r].begin(); 
    int curr_height = posH < sz(h[r]) ? (h[r][posH] - c + 1) : (C - c + 1);
    if(res.first < curr_height) { 
     res.first = curr_height; 
     res.second = 1; 
    } else if(res.first == curr_height) { 
      res.second++; 
    }
    for(int curr_row = r + 1; curr_row <= R; curr_row++) { 
     posH = lower_bound(h[curr_row].begin(), h[curr_row].end(), c) - h[curr_row].begin(); 
     curr_height = min(curr_height, posH < sz(h[curr_row]) ? (h[curr_row][posH] - c + 1) : (C - c + 1));
     int posV = lower_bound(v[curr_row - 1].begin(), v[curr_row - 1].end(), c) - v[curr_row - 1].begin(); 
     curr_height = min(curr_height, posV < sz(v[curr_row - 1]) ? (v[curr_row - 1][posV] - c) : (C - c + 1));
     if(res.first < curr_height * (curr_row - r + 1)) { 
      res.first = curr_height * (curr_row - r + 1);
      res.second = 1;
     } else if(res.first == curr_height * (curr_row - r + 1)) { 
      res.second++; 
     }
     if(curr_height == 0) break; 
    } 
   }
  } 
  cout << res.first << ' ' << res.second << '\n'; 
 }
 else { 
  cin >> nH; 
  for(int i = 0, r, c; i < nH; i++) { 
   cin >> r >> c; 
   h[c].push_back(r); 
  }
  cin >> nV; 
  for(int i = 0, r, c; i < nV; i++) { 
   cin >> r >> c; 
   v[c].push_back(r); 
  }
  for(int i = 0; i < maxn; i++) { 
   sort(h[i].begin(), h[i].end()); 
   sort(v[i].begin(), v[i].end()); 
  }     
  pair<int, int>res = {0, 0}; 
  for(int c = 1; c <= C; c++) { 
   for(int r = 1; r <= R; r++) { 
    // The square top left is (r, c) 
    int posV = lower_bound(v[c].begin(), v[c].end(), r) - v[c].begin(); 
    int curr_height = posV < sz(v[c]) ? (v[c][posV] - r + 1) : (R - r + 1);
    if(res.first < curr_height) { 
     res.first = curr_height; 
     res.second = 1; 
    } else if(res.first == curr_height) { 
      res.second++; 
    }
    for(int curr_col = c + 1; curr_col <= C; curr_col++) { 
     posV = lower_bound(v[curr_col].begin(), v[curr_col].end(), r) - v[curr_col].begin(); 
     curr_height = min(curr_height, posV < sz(v[curr_col]) ? (v[curr_col][posV] - r + 1) : (R - r + 1));
     int posH = lower_bound(h[curr_col - 1].begin(), h[curr_col - 1].end(), r) - h[curr_col - 1].begin(); 
     curr_height = min(curr_height, posH < sz(h[curr_col - 1]) ? (h[curr_col - 1][posH] - r) : (R - r + 1));
     if(res.first < curr_height * (curr_col - c + 1)) { 
      res.first = curr_height * (curr_col - c + 1);
      res.second = 1;
     } else if(res.first == curr_height * (curr_col - c + 1)) { 
      res.second++; 
     }
     if(curr_height == 0) break; 
    } 
   }
  } 
  cout << res.first << ' ' << res.second << '\n'; 
 }
 return 0;
}