#include <bits/stdc++.h>

using namespace std; 

int main() {
 int N; 
 cin >> N; 
 map<int, int>mp; 
 for(int i = 0, x; i < N; i++) { 
  cin >> x; 
  mp[abs(x)] += x; 
 } 
 for(auto [key, value] : mp) { 
  if(mp[key] != 0) { 
    cout << -mp[key] << '\n'; 
  } 
 } 
 return 0; 
}