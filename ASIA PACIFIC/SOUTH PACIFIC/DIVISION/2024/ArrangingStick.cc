#include <bits/stdc++.h> 

using namespace std; 

int main() {
  int N; 
  cin >> N; 
  set<int>ms; 
  for(int i = 0, x; i < N; i++) {
    cin >> x; 
    ms.insert(x); 
  } 
  for(int i = 0; i < N; i++) { 
   if(i & 1) { 
    cout << *prev(ms.end()) << ' '; 
    ms.erase(*prev(ms.end())); 
   } 
   else { 
    cout << *ms.begin() << ' '; 
    ms.erase(*ms.begin()); 
   } 
  } 
  return 0;
}