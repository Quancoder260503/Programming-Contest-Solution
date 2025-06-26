#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N;  
 cin >> N; 
 vector<pair<int, int>>a(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i].first >> a[i].second; 
  for(int j = 0; j < i; j++) { 
   if(a[i].first < a[j].first || a[i].second < a[j].second) { 
    cout << "no\n"; 
    return 0; 
   }
   if(a[i].first == a[j].first && a[i].second == a[j].second) { 
    cout << "no\n"; 
    return 0; 
   }
  }
 }
 cout << "yes\n"; 
 return 0; 
}
