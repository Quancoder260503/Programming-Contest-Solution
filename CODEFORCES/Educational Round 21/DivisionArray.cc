#include "bits/stdc++.h"

using namespace std; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  multiset<int64_t>s1, s2;
  vector<int>a(N);
  int64_t sum1 = 0, sum2 = 0;   
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
    sum2 += a[i]; 
    s2.insert(a[i]); 
  }
  if(sum2 % 2 != 0) { 
    cout << "NO\n"; 
    return 0; 
  }
  int flag = false; 
  for(int i = 0; i < N; i++) { 
    if(sum1 == sum2) { 
      flag = true;
      break; 
    }
    if(sum1 > sum2) { 
       if((sum1 - sum2) % 2 == 0 && s1.count((sum1 - sum2) / 2)) { 
         flag = true;
         break; 
       }
    }
    else { 
       if((sum2 - sum1) % 2 == 0 && s2.count((sum2 - sum1) / 2)) { 
         flag = true; 
         break; 
       }
    }
    sum1 += a[i]; 
    sum2 -= a[i];
    s1.insert(a[i]); 
    s2.erase(s2.find(a[i])); 
  }
  cout << (flag ? "YES" : "NO") << '\n'; 
  return 0; 
}