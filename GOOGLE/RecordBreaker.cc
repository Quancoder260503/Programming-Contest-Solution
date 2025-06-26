#include "bits/stdc++.h"

using namespace std;

const int oo = 1e9; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, T; 
  int _case = 0; 
  for(cin >> T; T--; ) { 
   _case++; 
   cin >> N; 
   vector<int>a(N); 
   int max_so_far = -oo; 
   for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
   }
   int ret = 0; 
   for(int i = 0; i < N; i++) { 
    if((a[i] > max_so_far)) { 
     if(i + 1 < N && a[i] > a[i + 1]) { 
       ret++; 
     } else if(i + 1 == N) { 
       ret++; 
     }
    }
    max_so_far = max(max_so_far, a[i]); 
   }
   printf("Case #%d: %d\n", _case, ret); 
  }
  return 0;
}
