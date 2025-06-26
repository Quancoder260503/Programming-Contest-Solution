#include "bits/stdc++.h"
using namespace std; 

#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, K, Prob; 
 cin >> N >> K >> Prob; 
 vector<string>strategy = {"continue", "backspace", "restart"};
 // Finish all the way to the end
 Prob = 100 - Prob; 
 int expected_continue  = Prob * (N - K + 1) + (100 - Prob) * (N - K + 1 + 4 + N); 
 int expected_backspace = Prob * (N - K + 1 + 1 + 4 + N) + (100 - Prob) * (N - K + 1 + 1);
 int expected_restart   = 300 + N * 100 + 100; 
 int opt = min({expected_backspace, expected_continue, expected_restart});
// cout << expected_continue << " " << expected_restart << " " << expected_backspace << '\n'; 
 int ptr = 0; 
 for(auto x : {expected_continue, expected_backspace, expected_restart}){
  if(x == opt) { 
    cout << strategy[ptr] << '\n';  
    break; 
  }
  ptr++; 
 }
 return 0; 
}