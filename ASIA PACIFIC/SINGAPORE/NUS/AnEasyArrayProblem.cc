#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int64_t oo = 1e17; 
const int maxn = 5e5 + 10; 

struct Node { 
  int64_t max_1, max_2, min_1, min_2; 
  Node() { 
   max_1 = max_2 = -oo; 
   min_1 = min_2 = oo; 
  }
  Node operator + (const Node &other) { 
   Node ret; 
   ret.max_1 = max(max_1, other.max_1); 
   ret.max_2 = max({min(max_1, other.max_1), max_2, other.max_2}); 
   ret.min_1 = min(min_1, other.min_1); 
   ret.min_2 = min({max(min_1, other.min_1), min_2, other.min_2}); 
   return ret; 
  }; 
}; 

Node tree[maxn << 2]; 
Node null_node; 
int N, Q; 

void update(int pos, int val, int L = 1, int R = N, int p = 1) { 
 if(L == R) { 
  tree[p].min_1 = tree[p].max_1 = val; 
  return; 
 }
 int mid = (L + R) / 2; 
 if(pos <= mid) update(pos, val, L, mid, p << 1); 
 else update(pos, val, mid + 1, R, p << 1 | 1); 
 tree[p] = tree[p << 1] + tree[p << 1 | 1]; 
 return; 
}

Node query(int tl, int tr, int L = 1, int R = N, int p = 1) { 
 if(tr < L || R < tl) return null_node; 
 if(tl <= L && R <= tr) return tree[p]; 
 int mid = (L + R) / 2; 
 return query(tl, tr, L, mid, p << 1) + query(tl, tr, mid + 1, R, p << 1 | 1); 
}

int main(void) {
  ios_base::sync_with_stdio(0); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N >> Q;
  vector<int64_t>a(N); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
    update(i + 1, a[i]); 
  }
  for(int i = 0, L, R; i < Q; i++) { 
   cin >> L >> R; 
   Node ret = query(L + 1, R - 1); 
   --L, --R; 
   cout << max({1LL * a[L] * a[R] * ret.max_1 * ret.max_2, 
                1LL * a[L] * a[R] * ret.max_1 * ret.min_1, 
                1LL * a[L] * a[R] * ret.min_1 * ret.min_2}) << '\n'; 
  }
  return 0; 
}
