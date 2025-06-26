#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int oo = 1e9; 

struct node { 
  int left, right, sum; 
  node() { 
   left = right = sum = 0; 
   return; 
  }
  node operator + (const node &other) { 
   node ret = node(); 
   ret.left  = left;
   ret.right = other.right;
   ret.sum = sum + other.sum - (right > 0 && other.left > 0); 
   return ret; 
  }
}; 

const int MAXN = 2e5 + 10; 

int N, Q;
node tree[MAXN << 2], null_node;

void update(int pos, int tl = 1, int tr = N, int p = 1) { 
 if(tl == tr) {
  tree[p].left = tree[p].right = tree[p].sum = 1; 
  return; 
 }
 int mid = (tl + tr) / 2;
 if(pos <= mid) update(pos, tl, mid, p << 1); 
 else           update(pos, mid + 1, tr, p << 1 | 1); 
 tree[p] = tree[p << 1] + tree[p << 1 | 1]; 
 return; 
}


node query(int L, int R, int tl = 1, int tr = N, int p = 1) { 
 if(L > tr || R < tl) return null_node; 
 if(L <= tl && tr <= R) return tree[p]; 
 int mid = (tl + tr) / 2;
 return query(L, R, tl, mid, p << 1) + query(L, R, mid + 1, tr, p << 1 | 1); 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N >> Q;
  vector<array<int, 4>>ord; 
  for(int i = 0, x; i < N; i++) { 
   cin >> x; 
   ord.push_back({x, -1, -1, i + 1}); 
  }
  for(int i = 0, L, R, x; i < Q; i++) { 
   cin >> L >> R >> x; 
   ord.push_back({x, L, R, i}); 
  }
  sort(ord.rbegin(), ord.rend()); 
  vector<int>ret(Q); 
  for(auto [x, L, R, ind] : ord) { 
   if(L == -1) { 
    update(ind); 
   } else { 
    ret[ind] = query(L, R).sum; 
   }
  }
  for(auto &x : ret) cout << x << '\n'; 
  return 0; 
}