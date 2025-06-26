#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxf = 1 << 18; 

int N, a[maxf], l[maxf], r[maxf]; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 scanf("%d", &N); 
 a[0] = a[N + 1] = 0x3f3f3f3f; 
 for(int i = 1; i <= N; i++) { 
  scanf("%d", &a[i]); 
 }
 for(int i = 1; i <= N; i++) { 
  l[i] = i - 1; 
  while((a[l[i]] | a[i]) == a[i]) l[i] = l[l[i]]; 
 }
 for(int i = N; i >= 1; i--) { 
  r[i] = i + 1; 
  while((a[r[i]] | a[i]) == a[i] && a[r[i]] != a[i]) r[i] = r[r[i]]; 
 }
 int64_t ret = 1LL * N * (N + 1) / 2; 
 for(int i = 1; i <= N; i++) { 
  ret = ret - 1LL * (i - l[i]) * (r[i] - i); 
 }
 cout << ret << '\n'; 
 return 0; 
}