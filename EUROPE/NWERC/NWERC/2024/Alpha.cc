#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
 int N; 
 cin >> N; 
 vector<pair<string, string>>ps; 
 cin.ignore(); 
 string S; 
 for(int i = 0; i < N; i++) { 
  getline(cin, S);  
  for(int j = 0; j < sz(S); j++) { 
   if('A' <= S[j] && S[j] <= 'Z') {
    ps.push_back({S.substr(j), S});  
    break; 
   }
  }
 }
 sort(ps.begin(), ps.end()); 
 for(auto [_, y] : ps) cout << y << '\n'; 
 return 0; 
}