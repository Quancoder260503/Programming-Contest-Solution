#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(nullptr); 
 cout.tie(nullptr); 
 int n, k; 
 cin >> n >> k; 
 vector<int>arr(n); 
 iota(arr.begin(), arr.end(), 1); 
 std::random_device rd;
 std::mt19937 rng(rd());
 vector<int>ret; 
 while(true) {
  shuffle(arr.begin(), arr.end(), rng);  
  vector<int>winner{arr[0]}; 
  vector<int>nxt;  
  for(int i = 1; i < arr.size(); i++) { 
   cout << "? " << arr[0] << " " << arr[i] << '\n'; 
   cout.flush(); 
   string res; 
   cin >> res;
   if(stoi(res) == arr[i]) { 
    winner.push_back(arr[i]);
   } else { 
    nxt.push_back(arr[i]); 
   }
  }
  if(sz(winner) <= k) { 
    k = k - sz(winner); 
    for(auto &x : winner) ret.push_back(x);
    arr = nxt;  
  } else { 
    arr = winner; 
  }
  if(k == 0) break; 
 }
 cout << "! "; 
 for(auto &x : ret) cout << x << " "; 
 return 0; 
}

