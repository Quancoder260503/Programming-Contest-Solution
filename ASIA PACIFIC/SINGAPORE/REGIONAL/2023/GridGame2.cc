#include <bits/stdc++.h>

using namespace std; 

#define sz(x) int(x.size())

int nimber(int x, int y) { 
 return y > 0 ? (x / y % 2) ^ nimber(y, x % y) : 0; 
} 

int grundy(int x, int y) { 
 return nimber(x - 1, y) ^ nimber(x, y - 1) ^ nimber(x - 1, y - 1) ^ nimber(x, y); 
} 

int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int N; 
 cin >> N; 
 int ret = 0; 
 for(int i = 0, x, y; i < N; i++) { 
  cin >> x >> y; 
  ret = ret ^ grundy(x, y); 
 }
 cout << (ret ? "FIRST" : "SECOND") << '\n'; 
 return 0;
}