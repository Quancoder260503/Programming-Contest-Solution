#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
const int maxf = 1e5 + 5;

int a[maxf]; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  for(int i = 0, x; i < N; i++) { 
    cin >> a[i]; 
  }
  sort(a, a + N);
  int64_t sum = 0; 
  for(int i = 0; i < N; i++) { 
    sum += a[i]; 
  }
  if(sum % 2 == 0 && 2 * a[N - 1] <= sum) { 
    cout << "YES\n"; 
  }
  else { 
    cout << "NO\n"; 
  }
  return 0; 
}
