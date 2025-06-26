#include "bits/stdc++.h" 

using namespace std; 
#define sz(x) int(x.size())

struct fenwick { 
  vector<int>bit; 
  int n; 
  fenwick(int _n) { 
   n = _n; 
   bit.resize(n + 1);  
  }
  void add(int i, int x) { 
   for(i++ ; i < n; i += (i & -i)) { 
    bit[i] += x; 
   }
  }
  int64_t query(int i) { 
   int64_t ret = 0; 
   for(i++; i > 0; i -= (i & -i)) { 
    ret += bit[i]; 
   }
   return ret; 
  }
}; 

int64_t f(vector<int>&arr, int n) { 
 int64_t ret = 0; 
 fenwick fenw(n + 7); 
 for(int i = sz(arr) - 1; i >= 0; i--) { 
  ret += fenw.query(arr[i]); 
  fenw.add(arr[i], 1); 
  //cout << ret << " " << arr[i] << '\n'; 
 }
 return ret; 
}

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int N, T; 
 for(cin >> T; T--; ) { 
  cin >> N; 
  vector<int>even, odd; 
  for(int i = 0, x; i < N; i++) { 
   cin >> x; 
   (i & 1 ? odd : even).push_back(x); 
  }
  int x1 = 0, y1 = 0; 
  int state = f(odd, N) % 2 != f(even, N) % 2; 
  sort(odd.begin(), odd.end()); 
  sort(even.begin(), even.end()); 
  vector<int>ret; 
  for(int i = 0, x1 = 0, x2 = 0; i < N; i++) { 
   if(i & 1) ret.push_back(odd[x1++]); 
   else      ret.push_back(even[x2++]); 
  }
  if(state) {
    swap(ret[N - 3], ret[N - 1]); 
  }
  for(auto &x : ret) { 
   cout << x << " "; 
  }
  cout << '\n'; 
 }
 return 0; 
}