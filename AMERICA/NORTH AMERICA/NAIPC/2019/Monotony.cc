#include "bits/stdc++.h"

using namespace std;

const int LOG = 21; 
const int maxf = (1 << LOG); 

int64_t dyn[maxf][LOG]; 

int main(void) { 
   ios_base::sync_with_stdio(0); 
   cin.tie(0); 
   cout.tie(0);
   int r, c; 
   cin >> r >> c; 
   vector<vector<int>>a(r, vector<int>(c)); 
   for(int i = 0; i < r; i++)
   for(int j = 0; j < c; j++) { 
      cin >> a[i][j]; 
   }
   vector<vector<int>>T(r, vector<int>(r)); 
   for(int i = 0; i < r; i++)
   for(int j = 0; j < i; j++) 
   for(int k = 0; k < c; k++) if(a[i][k] > a[j][k]) { 
      T[j][i] |= (1 << k); 
   }
   int64_t ret = 0;  
   for(int mask = 1; mask < (1 << c); mask++) { 
      vector<int>row; 
      for(int i = 0; i < r; i++) { 
         int last = 0, good = true; 
         for(int j = 0; j < c; j++) if(mask & (1 << j)) { 
            if(last < a[i][j]) { 
               last = a[i][j]; 
            }
            else { 
               good = false; 
            }
         }
         if(good) { row.push_back(i); continue; } 
         last = 0; good = true;
         for(int j = c - 1; j >= 0; j--) if(mask & (1 << j)) { 
            if(last < a[i][j]) { 
               last = a[i][j]; 
            }
            else { 
               good = false; 
            }
         }
         if(good) { row.push_back(i); }
      }
      ret += int(row.size());
      for(int i = 0; i < row.size(); i++)
      for(int j = 0; j < i; j++) { 
         int gmask = T[row[j]][row[i]] & mask; 
         dyn[gmask][row[i]] += 1 + dyn[gmask][row[j]];
      } 
      for(int i = 0; i < row.size(); i++)
      for(int j = i + 1; j < row.size(); j++) { 
         int gmask = T[row[i]][row[j]] & mask; 
         ret += dyn[gmask][row[j]]; 
         dyn[gmask][row[j]] = 0; 
      }
   }
   cout << ret << '\n'; 
   return 0; 
}
/* 
   For each mask of the column, only consider the mask that has monotone increasing / decreasing order  
*/ 
