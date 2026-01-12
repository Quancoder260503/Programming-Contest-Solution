#include <vector> 
#include <iostream> 
#include <unordered_set> 
#include <array> 
#include <map> 
#include <stack> 
#include <cstring> 
#include <assert.h> 

#define sz(x) int(x.size())

using namespace std; 

using ll = long long; 

const int maxn = 5e5 + 10;
int pos[maxn]; 
string S; 
int N; 
map<pair<int, int>, int>cache; 
int Grundy_range(int i, int j) { 
 if(i + 1 == j) return 1; 
 if(i >= j) return 0; 
 if(cache.count({i, j})) return cache[{i, j}]; 
 if(pos[j] == i) { 
  return 1 + Grundy_range(i + 1, j - 1);   
 }
 int ret = (Grundy_range(i, pos[j] - 1) ^ Grundy_range(pos[j], j));
 return cache[{i, j}] = ret; 
}
int wi, wj; 
void Grundy_track(int i, int j, int target_xor) {
 if(i + 1 == j) {  
  if(target_xor == 0) { 
   wi = i, wj = j; 
  }
  return;   
 }
 if(target_xor == 0 && pos[j] == i) { 
  wi = i, wj = j; 
  return; 
 }
 if(pos[j] == i) { 
  Grundy_track(i + 1, j - 1, target_xor - 1);  
  return;  
 }
 Grundy_track(i, pos[j] - 1, (target_xor) ^ Grundy_range(pos[j], j));
 Grundy_track(pos[j], j,     (target_xor) ^ Grundy_range(i, pos[j] - 1));  
 return; 
}
int main(void) {    
 int tc; 
 for(cin >> tc; tc--; ) {  
  cin >> N >> S; 
  N = 2 * N; 
  stack<int>stk;
  cache.clear(); 
  for(int i = 0; i < N; i++) pos[i] = -1; 
  for(int i = 0; i < N; i++) { 
   if(S[i] == '(')  { 
    stk.push(i);  
   } else { 
    if(sz(stk)) {
     pos[i] = stk.top();  
     stk.pop(); 
    }
   }
  }
  int sum_xor = Grundy_range(0, N - 1); 
  cout << (sum_xor ? "Let's cook!" : "Let's hope David throws ...") << '\n'; 
  if(sum_xor) { 
   if(pos[N - 1] == 0) { 
    cout << 1 << " " << N << '\n'; 
    continue;
   }
   wi = -1, wj = -1;  
   Grundy_track(0, pos[N - 1] - 1, Grundy_range(pos[N - 1], N - 1)); 
   Grundy_track(pos[N - 1], N - 1, Grundy_range(0, pos[N - 1] - 1)); 
   cout << wi + 1 << " " << wj + 1 << '\n'; 
  }
 }
 return 0; 
}
