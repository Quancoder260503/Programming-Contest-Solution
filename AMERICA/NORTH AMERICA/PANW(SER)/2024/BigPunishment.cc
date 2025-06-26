#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
 
void solve() {
 string a, b; 
 cin >> a >> b; 
 if(sz(a) > sz(b)) swap(a, b); 
 if(sz(a) != sz(b)) { 
    if(a > b) { 
    cout << "NO\n"; 
    return; 
    
    } else if(a < b) { 
    cout << "YES\n"; 
    return; 
    }
 }
 for(int i = 0; i < sz(a); i++) { 
  if(a[i] < b[i]) { 
   if('a' <= b[i] && b[i] <= 'z' && 'A' <= a[i] && a[i] <= 'Z') { 
     cout << "NO\n"; 
   } else {
     cout << "YES\n"; 
   } 
   break; 
  }
  else if(a[i] > b[i]) { 
   if('a' <= a[i] && a[i] <= 'z' && 'A' <= b[i] && b[i] <= 'Z') { 
     cout << "NO\n"; 
   } else {
     cout << "YES\n"; 
   }   
   break; 
  } 
 }
 return; 
}

int main() { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int T;
 for(cin >> T; T--; ) { 
  solve(); 
 } 
 return 0; 
} 