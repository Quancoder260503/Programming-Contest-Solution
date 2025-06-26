#include "bits/stdc++.h"

using namespace std;

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  string S1, S2; 
  int N; 
  cin >> N; 
  vector<pair<int, string>>ret; 
  for(int i = 0; i < N; i++) { 
    cin >> S1 >> S2; 
    if(isdigit(S1[0])) { 
        ret.push_back({stoi(S1), S2}); 
    }
    else { 
        ret.push_back({2 * stoi(S2), S1}); 
    }
  }  
  sort(ret.begin(), ret.end()); 
  for(auto [_, x] : ret) { 
    cout << x << '\n'; 
  }
  return 0; 
}