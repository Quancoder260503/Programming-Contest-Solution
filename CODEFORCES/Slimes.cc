#include "bits/stdc++.h"

using namespace std;

void solve() {
 int N; 
 cin >> N; 
 vector<int>a(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 vector<int>ans(N, N); 
 for(int w = 0; w < 2; w++) { 
  vector<int64_t>prefix(N + 1); 
  for(int i = 0; i < N; i++) { 
   prefix[i + 1] = prefix[i] + a[i]; 
  }
  vector<int>p(N, -1); 
  for(int i = 1; i < N; i++) { 
   int pos = (w ? N - 1 - i : i); 
   int L = 1, R = i; 
   while(L <= R) { 
    int mid = (L + R) / 2; 
    if(prefix[i] > prefix[i - mid] + a[i] && p[i - 1] >= i - mid) { 
     ans[pos] = min(ans[pos], mid); 
     R = mid - 1; 
    } else { 
     L = mid + 1; 
    }
   }
   if(a[i - 1] > a[i]) ans[pos] = 1; 
   p[i] = (a[i] == a[i - 1] ? p[i - 1] : i - 1); 
  }
  reverse(a.begin(), a.end()); 
 }
 for(auto &x : ans) cout << (x == N ? -1 : x) << " "; 
 cout << '\n'; 
 return; 
}

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int T; 
 for(cin >> T; T--; ) { solve(); }
 return 0;
}
