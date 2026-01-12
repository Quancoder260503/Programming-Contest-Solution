#include "bits/stdc++.h"

using namespace std;

struct Tree {
  typedef int64_t T;
  static constexpr T unit = int64_t(0);
  T f(T a, T b) { return a + b; }  // (any associative fn)
  vector<T> s;
  int n;
  Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
  void update(int pos, T val) {
    pos += n;
    s[pos] = val; 
    for (; pos /= 2;) s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) {  // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  vector<Tree>tree; 
  int N, Q; 
  cin >> N >> Q;
  vector<int>a(N);  
  for(int i = 0; i < 9; i++) { 
   tree.push_back(Tree(N));
  }
  for(int i = 0; i < N; i++) { 
   string s = to_string(i + 1);
   cin >> a[i];  
   for(int j = 1; j < 10; j++) { 
    if((i + 1) % j == 0) { 
     tree[j - 1].update(i, 2 * a[i]); 
    } else { 
      auto it = find(s.begin(), s.end(), '0' + j); 
      if(it != s.end()) { 
        tree[j - 1].update(i, 2 * a[i]); 
      } else { 
        tree[j - 1].update(i, a[i]); 
      } 
    }
   }
  }
  for(int i = 0, c, L, R, k; i < Q; i++) { 
   cin >> c; 
   if(c == 1) { 
    cin >> L >> k; 
    string s = to_string(L);
    for(int j = 1; j < 10; j++) { 
     if(L % j == 0) { 
      tree[j - 1].update(L - 1, 2 * k);   
     } else { 
      auto it = find(s.begin(), s.end(), '0' + j); 
      if(it != s.end()) { 
        tree[j - 1].update(L - 1, 2 * k); 
      } else { 
        tree[j - 1].update(L - 1, k); 
      }
     }
    }
   } else { 
    cin >> L >> R >> k; 
    --L; 
    cout << tree[k - 1].query(L, R) << '\n'; 
   }
  }
  return 0;
}
