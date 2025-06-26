#include <bits/stdc++.h>

using namespace std; 

#define sz(x) int(x.size())

const int _N = 1 << 20; 

int tree[_N], lazy[_N]; 

void push_down(int p, int l, int mid, int r) {
  if (lazy[p] != -1) {
    lazy[2 * p] = lazy[p];
    lazy[2 * p + 1] = lazy[p];
    tree[2 * p] = lazy[p] * (mid - l + 1);
    tree[2 * p + 1] = lazy[p] * (r - mid);
    lazy[p] = -1;
  }
  return;
}
void update(int val, int L, int R, int l, int r, int p = 1) {
  if (L > r || R < l) return;
  if (L <= l && r <= R) {
    tree[p] = val * (r - l + 1);
    lazy[p] = val;
    return;
  }
  int mid = (l + r) >> 1;
  push_down(p, l, mid, r);
  update(val, L, R, l, mid, 2 * p);
  update(val, L, R, mid + 1, r, 2 * p + 1);
  tree[p] = tree[2 * p] + tree[2 * p + 1];
}


int query(int L, int R, int l, int r, int p = 1) {  
  if (L > r || R < l) return 0;
  if (L <= l && r <= R) return tree[p]; 
  int mid = (l + r) >> 1;
  push_down(p, l, mid, r);
  return query(L, R, l, mid, 2 * p) + query(L, R, mid + 1, r, 2 * p + 1); 
} 

int main() {
  int N, W; 
  cin >> N >> W; 
  vector<int>a(N); 
  memset(lazy, -1, sizeof(lazy)); 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  } 
  vector<int>h(W + 1); 
  set<int>ms; 
  ms.insert(1); 
  ms.insert(W + 1); 
  for(int i = 1; i <= W; i++) { 
   update(1, i, i, 1, W); 
  } 
  for(int i = 0; i < N; i++) {
   int c = query(a[i], a[i], 1, W); 
   update(0, a[i], a[i], 1, W); 
   if(a[i] > 1 && !ms.count(a[i])) { 
    int cc = query(a[i] - 1, a[i] - 1, 1, W); 
    if((cc | c) && abs(h[a[i] - 1] - (h[a[i]] + 1)) <= 1) { 
      update(1, a[i], a[i], 1, W); 
    } 
   } 
   if(a[i] < W && !ms.count(a[i] + 1)) {
    int cc = query(a[i] + 1, a[i] + 1, 1, W); 
    if((cc | c) && abs(h[a[i] + 1] - (h[a[i]] + 1)) <= 1) { 
      update(1, a[i], a[i], 1, W); 
    } 
   } 
   h[a[i]] += 1;
   if(a[i] > 1) {
    if(abs(h[a[i]] - h[a[i] - 1]) > 1) { 
     ms.insert(a[i]); 
    } 
    else {
     ms.erase(a[i]); 
     if(query(a[i] - 1, a[i] - 1, 1, W) == 1) { 
      update(1, a[i], a[i], 1, W); 
     } 
    }
   } 
   if(a[i] < W) { 
    if(abs(h[a[i]] - h[a[i] + 1]) > 1) { 
      ms.insert(a[i] + 1); 
    } 
    else { 
     ms.erase(a[i] + 1); 
     if(query(a[i] + 1, a[i] + 1, 1, W) == 1) { 
      update(1, a[i], a[i], 1, W); 
     } 
    } 
   }   
   if(query(a[i], a[i], 1, W) == 1) { 
    auto it = ms.lower_bound(a[i]);   
    if(a[i] <= *it - 1) { 
      update(1, a[i], *it - 1, 1, W);
    }
    it--; 
    if(*it <= a[i] && !ms.count(a[i])) { 
      update(1,*it, a[i], 1, W); 
    } 
   }
   if(query(1, W, 1, W) == 0) { 
    // No surviveable location 
    cout << i + 1 << '\n'; 
    exit(0); 
   } 
  } 
  cout << N + 1 << '\n'; 
  return 0;
}
