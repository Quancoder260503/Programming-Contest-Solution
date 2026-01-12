#include "bits/stdc++.h"

using namespace std;

template <typename T>
struct fenwick {
  vector<T> bit;
  int n;
  fenwick(int _n) : n(_n) { bit.resize(n); }
  void update(int pos, T v) {
    for (pos++; pos < n; pos += (pos & -pos)) {
      bit[pos] += v;
    }
    return;
  }
  T query(int pos) {
    T sum = 0;
    for (pos++; pos > 0; pos -= (pos & -pos)) {
      sum += bit[pos];
    }
    return sum;
  }
  T query(int L, int R) { return max(0, query(R) - query(L - 1)); }
};

const int maxn = (1 << 18) + 2; 
unordered_map<int, int>visited[maxn]; 

void rec(int L, int R, vector<int>&vis, vector<int>&a, fenwick<int>&fenwick) { 
 if(L == R) { 
  return; 
 }
 int mid = (L + R) / 2;
 int ok = false;  
 if(!vis[a[L]]) { 
  vis[a[L]] = 1;
  ok = true; 
  for(int i = L; i <= R; i++) { 
   fenwick.update(a[i], -1); 
  } 
  for(int i = L + 1; i <= R; i++) if(a[L] > a[i] + 1) { 
   int curr = fenwick.query(a[i] + 1, a[L] - 1); 
 //  cout << L << " " << R << " " << curr << " " << a[L] + 1 << " " << a[i] + 1 << '\n'; 
   if(curr > 0) {
   // cout << a[L] << " " << a[i] << '\n'; 
    visited[a[L]][a[i]] = 1;
   } 
  }
  for(int i = L + 1; i <= R; i++) { 
   fenwick.update(a[i], 1); 
  }
 }
 rec(L, mid, vis, a, fenwick); 
 rec(mid + 1, R, vis, a, fenwick);
 if(ok) { 
  fenwick.update(a[L], 1); 
 }
 return;  
}

vector<int> early_bird(int L, int R, vector<int>& a) {
  if (L == R) {
    return vector<int>{a[L]};
  }
  int mid = (L + R) / 2;
  int winner = a[L]; 
  vector<int> better_left, worse_left, better_right, worse_right;

  vector<int> left_branch = early_bird(L, mid, a);
  vector<int> right_branch = early_bird(mid + 1, R, a); 
  
  
  for (int i = 0, ok = true; i < left_branch.size(); i++) {
    if (left_branch[i] == winner) {
      ok = false;
      continue;
    }
    (ok ? better_left : worse_left).push_back(left_branch[i]);
  }


  for (int i = 0; i < right_branch.size(); i++) {
    (visited[winner].count(right_branch[i]) ? better_right : worse_right).push_back(right_branch[i]);
  }
  vector<int> ret;
  int i = 0, j = 0;
  while (i < better_left.size() && j < better_right.size()) {
    if (better_left[i] < better_right[j]) {
      ret.push_back(better_left[i]);
      i++;
    } else {
      ret.push_back(better_right[j]);
      j++;
    }
  }
  while (i < better_left.size()) {
    ret.push_back(better_left[i]);
    i++;
  }
  while (j < better_right.size()) {
    ret.push_back(better_right[j]);
    j++;
  }
  ret.push_back(winner);
  i = 0, j = 0;
  while (i < worse_left.size() && j < worse_right.size()) {
    if (worse_left[i] < worse_right[j]) {
      ret.push_back(worse_left[i]);
      i++;
    } else {
      ret.push_back(worse_right[j]);
      j++;
    }
  }
  while (i < worse_left.size()) {
    ret.push_back(worse_left[i]);
    i++;
  }
  while (j < worse_right.size()) {
    ret.push_back(worse_right[j]);
    j++;
  }
  return ret;
}

void solve() {
  int n;
  cin >> n;
  n = (1 << n);
  for(int i = 0; i < maxn; i++) { 
   visited[i].clear(); 
  }
  vector<int> a(n);
  vector<int>vis(n + 1); 
  fenwick<int> fenw(n + 7); 
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    fenw.update(a[i], 1); 
  }
  rec(0, n - 1, vis, a, fenw); 
  vector<int> ret = early_bird(0, n - 1, a);
  for(auto &x : ret) cout << x << " "; 
  cout << '\n';
  return; 
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  for (T = 1; T--;) { 
    solve();
  }
  return 0;
}
