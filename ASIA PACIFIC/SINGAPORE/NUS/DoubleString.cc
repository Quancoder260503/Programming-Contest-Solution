#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <stack> 
#include <cmath>
#include <ext/pb_ds/assoc_container.hpp>
 
 
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
 
using namespace std;
 
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
 
using namespace __gnu_pbds;
template <class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
/*
0  $ 
1  $i
2  $ippi
3  $issippi
4  $ississippi 
5  $mississippi
6  $pi
7  $ppi
8  $sippi
9  $sissippi
10 $ssippi
11 $ssissippi
*/
 
 
struct SuffixArray {
 vector<int>sa, rsa, lcp;
 SuffixArray(string s, int lim = 256) {
  s.push_back(0);
  int n = sz(s), k = 0, a, b;
  vector<int>x(all(s)), y(n), ws(max(n, lim));
  sa = lcp = y;
  iota(all(sa), 0);
  for(int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
   p = j, iota(all(y), n - j);
   for(int i = 0; i < n; i++) if(sa[i] >= j) {
    y[p++] = sa[i] - j;
   }
   fill(all(ws), 0);
   for(int i = 0; i < n; i++) {
    ws[x[i]]++;
   }
   for(int i = 1; i < lim; i++) {
    ws[i] += ws[i - 1];
   }
   for(int i = n; i--; ) sa[--ws[x[y[i]]]] = y[i];
   swap(x, y), p = 1, x[sa[0]] = 0;
   for(int i = 1; i < n; i++) {
    a = sa[i - 1], b = sa[i];
    x[b] = (y[a] == y[b] && y[a + j] == y[b + j] ? p - 1 : p++);
   }
  }
  for(int i = 0, j; i < n - 1; lcp[x[i++]] = k) {
   for(k && k--, j = sa[x[i] - 1]; s[i + k] == s[j + k]; k++);
  }
  // lcp[i] = LCP(i, i - 1), lcp[0] = 0 
  //for(int i = 0; i < sz(sa); i++) cout << sa[i] <<" " << lcp[i] << '\n'; 
  // decompose into different interval
 }
};

struct segtree {
  string a;
  int n;
  vector<pair<int, int>> tree;
  segtree(int n) : n(n), tree(4 * n + 7) {} 
  void update(int v, int vl, int vr, int pos, int val) {
    if (vl == vr) {
      tree[v] = {val, vl};  
      return;
    }
    int vm = (vl + vr) / 2;
    if(pos <= vm) update(v << 1, vl, vm, pos, val);
    else          update(v << 1 | 1, vm + 1, vr, pos, val);
    tree[v] = min(tree[v << 1 | 1], tree[v << 1]); 
    return; 
  }
  pair<int, int> query(int v, int vl, int vr, int L, int R) { 
   if(R < vl || vr < L) return {1e9, 1}; 
   if(L <= vl && vr <= R) return tree[v]; 
   int mid = (vl + vr) / 2; 
   return min(query(v << 1, vl, mid, L, R), query(v << 1 | 1, mid + 1, vr, L, R)); 
  }
};
 
int64_t dnq(int l, int r, segtree&tree_lcp, Tree<pair<int, int>>&tree_sa, SuffixArray &sa) { 
  if(l + 1 >= r)  return 0;
  auto min_element = tree_lcp.query(1, 1, sz(sa.sa) - 1, l + 1, r - 1); 
  int mid = min_element.second; 
  int64_t ans = 0; 
  Tree<pair<int, int>>tree_sa_b; 
  if(mid - l < r - mid) { 
   for(int j = l; j < mid; j++) {
    tree_sa.erase(make_pair(sa.sa[j], j)); 
    tree_sa_b.insert(make_pair(sa.sa[j], j));  
   }
   if(sa.lcp[mid] > 0) { 
    for(int j = l; j < mid; j++) { 
     ans += tree_sa.order_of_key(make_pair(sa.sa[j] + 1, -1)) - tree_sa.order_of_key(make_pair(sa.sa[j] - min_element.first, -1));
     ans += tree_sa.order_of_key(make_pair(sa.sa[j] + min_element.first + 1, -1)) - tree_sa.order_of_key(make_pair(sa.sa[j], -1)); 
    }
   }
   ans += dnq(l, mid, tree_lcp, tree_sa_b, sa); 
   ans += dnq(mid, r, tree_lcp, tree_sa, sa); 
  } else { 
   for(int j = mid; j < r; j++) {
    tree_sa.erase(make_pair(sa.sa[j], j)); 
    tree_sa_b.insert(make_pair(sa.sa[j], j));  
   }
   if(sa.lcp[mid] > 0) { 
    for(int j = mid; j < r; j++) { 
     ans += tree_sa.order_of_key(make_pair(sa.sa[j] + 1, -1)) - tree_sa.order_of_key(make_pair(sa.sa[j] - min_element.first, -1));
     ans += tree_sa.order_of_key(make_pair(sa.sa[j] + min_element.first + 1, -1)) - tree_sa.order_of_key(make_pair(sa.sa[j], -1)); 
    }
   }
   ans += dnq(l, mid, tree_lcp, tree_sa, sa); 
   ans += dnq(mid, r, tree_lcp, tree_sa_b, sa); 
  } 
  return ans; 
}
 
int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 string s;
 cin >> s;
 SuffixArray sa(s);
 Tree<pair<int, int>>tree_sa;
 segtree seg_tree(sz(sa.sa)); 
 for(int i = 1; i < sz(sa.sa); i++) { 
   tree_sa.insert({sa.sa[i], i});
   seg_tree.update(1, 1, sz(sa.sa) - 1, i, sa.lcp[i]);  
 } 
 cout << dnq(1, sz(sa.sa), seg_tree, tree_sa, sa)  << '\n';
 return 0;
}