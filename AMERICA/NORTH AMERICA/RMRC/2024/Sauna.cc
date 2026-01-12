#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, T; 
 cin >> N; 
 vector<int>prefix(200005); 
 for(int i = 0, a, b; i < N; i++) { 
  cin >> a >> b; 
  prefix[a]++; 
  prefix[b + 1]--; 
 }
 for(int i = 1; i < 200005; i++) { 
  prefix[i] += prefix[i - 1]; 
 }
 int ret = 0, f = -1; 
 for(int i = 0; i < 200005; i++) { 
  if(prefix[i] == N) { 
   if(f == -1) f = i; 
   ret++; 
  }
 }
 if(ret == 0) cout << "bad news\n"; 
 else cout << ret << " " << f << '\n'; 
 return 0; 
}