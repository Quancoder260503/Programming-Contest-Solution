#include "bits/stdc++.h"

using namespace std;

#define ll long long 

const int maxn = 1e5 + 10;
const int LOG = 31;

struct node {
 node *child[2];
 int cnt; 
 node() {
  child[0] = child[1] = NULL;
  cnt = 0; 
 }
};


void insert(node *root, int k, int depth) {
 if(depth == 0) { 
  root->cnt++;
  return;
 } 
// cout << k << " " << depth << '\n'; 
 int c = k >> (depth - 1) & 1;
 if(!root->child[c]) root->child[c] = new node();
 insert(root->child[c], k, depth - 1);
 root->cnt = 0; 
 for(int i = 0; i < 2; i++) if(root->child[i]) {
  root->cnt += root->child[i]->cnt; 
 }
 return;
}

int query_a(node *root, int depth, int curr_v, int k, int equal) {
 if(!root) return 0;
 if(!equal) return root->cnt; 
 int ret = 0; 
 if(k >> (depth - 1) & 1) { 
  if(curr_v >> (depth - 1) & 1) { 
   ret += query_a(root->child[0], depth - 1, curr_v, k, equal); 
   if(!equal) ret += query_a(root->child[1], depth - 1, curr_v, k, equal); 
  } else { 
   if(!equal) ret += query_a(root->child[0], depth - 1, curr_v, k, equal);       
   ret += query_a(root->child[1], depth - 1, curr_v, k, equal); 
  }
 } else {
  if(curr_v >> (depth - 1) & 1) { 
   ret += query_a(root->child[0], depth - 1, curr_v, k, false); 
   ret += query_a(root->child[1], depth - 1, curr_v, k, equal);      
  } else { 
   ret += query_a(root->child[0], depth - 1, curr_v, k, equal); 
   ret += query_a(root->child[1], depth - 1, curr_v, k, false); 
  } 
 }
 return ret; 
} 

int query_b(node *root, int depth, int curr_v, int k, int equal, int equal_k) { 
 if(!root) return 0;
 if(!equal && !equal_k) return root->cnt; 
 int ret = 0; 
 if(k >> (depth - 1) & 1) { 
  if(curr_v >> (depth - 1) & 1) { 
   if(!equal)   ret += query_b(root->child[0], depth - 1, curr_v, k, equal, equal_k); 
   if(!equal_k) ret += query_b(root->child[1], depth - 1, curr_v, k, equal, equal_k); 
  } else { 
   if(!equal_k) ret += query_b(root->child[0], depth - 1, curr_v, k, equal, equal_k);       
   ret += query_b(root->child[1], depth - 1, curr_v, k, false, equal_k);
  }
 } else {
  if(curr_v >> (depth - 1) & 1) { 
   if(!equal)   ret += query_b(root->child[0], depth - 1, curr_v, k, equal, false); 
   ret += query_b(root->child[1], depth - 1, curr_v, k, equal, equal_k);      
  } else { 
   ret += query_b(root->child[0], depth - 1, curr_v, k, equal, equal_k); 
   ret += query_b(root->child[1], depth - 1, curr_v, k, false, false); 
  } 
 }
 return ret; 
} 

struct Fenwick { 
 vector<ll>bit;
 int n; 
 Fenwick(int _n) { 
  n = _n; 
  bit.assign(n, 0); 
 } 
 void reset() { 
  fill(bit.begin(), bit.end(), 0); 
 }
 void update(int pos, int v) { 
  for(pos++; pos < n; pos += pos & (-pos)) { 
   bit[pos] += v; 
  }
  return;     
 } 
 ll query(int pos) {
  ll sum = 0;  
  for(pos++; pos > 0; pos -= pos & (-pos)) { 
   sum += bit[pos]; 
  }
  return sum;  
 }
 ll query(int l, int r) { 
  return query(r) - query(l - 1); 
 } 
}; 

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 int n, k; 
 cin >> n >> k;
 vector<int>a(n); 
 for(auto &x : a) cin >> x; 
 ll inv = 0; 
 vector<int>coord; 
 Fenwick fenw(n + 3); 
 for(int i = 0; i < n; i++) { 
  coord.push_back(a[i]); 
 } 
 sort(coord.begin(), coord.end()); 
 coord.erase(unique(coord.begin(), coord.end())); 
 for(int i = n - 1; i >= 0; i--) {
  int pos = lower_bound(coord.begin(), coord.end(), a[i]) - coord.begin() + 1; 
  inv += fenw.query(pos - 1);
  fenw.update(pos, 1);
 }
 ll xor_ge = 0, xor_ge_inv = 0;
 node *root = new node();
 for(int i = 0; i < n; i++) { 
  xor_ge += query_a(root, LOG, a[i], k, true); 
  xor_ge_inv += query_b(root, LOG, a[i], k, true, true); 
  insert(root, a[i], LOG);    
 }
cout << inv + xor_ge - 2LL * xor_ge_inv << '\n';
/*
 cout << xor_ge << '\n';
 {
  int cnt = 0; 
  for(int i = 0; i < n; i++) { 
   for(int j = i + 1; j < n; j++) {
    int c = (a[i] ^ a[j]) > k; 
    int d = (a[i] > a[j]); 
    cnt += c;
   }
  }
  cout << cnt << '\n'; 
 }
 */
 return 0;
}
