#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int maxn = 1e5 + 10;
const int LOG = 18;

struct node {
 int mex, size, sum_xor;
 node *child[2];
 node() {
  child[0] = child[1] = NULL;
  mex = 0;
  size = 1;
  sum_xor = 0;
 }
};

node *root[maxn];
vector<int>g[maxn];
int n, col[maxn], grundy[maxn];

void push_down(node *root, int k) {
 if(k > 0) {
  int curr_value = root->sum_xor;
  if(curr_value >> (k - 1) & 1) {
   swap(root->child[0], root->child[1]);
  }
  if(root->child[0]) root->child[0]->sum_xor ^= curr_value;
  if(root->child[1]) root->child[1]->sum_xor ^= curr_value;
  root->sum_xor = 0;
 }
}

void update(node *root, int k) {
 if(k > 0) {
  int curr_size = 1 << (k - 1);
  if(root->child[0] && root->child[1]) {
   root->size = root->child[0]->size + root->child[1]->size;
   root->mex = (root->child[0]->size == curr_size ? curr_size + root->child[1]->mex : root->child[0]->mex);
  }
  else if(root->child[0]) {
   root->size = root->child[0]->size;
   root->mex = (root->child[0]->size == curr_size ? curr_size : root->child[0]->mex);
  }
  else if(root->child[1]) {
   root->size = root->child[1]->size;
   root->mex = 0;
  }
 }
 return;
}

void insert(node *root, int k, int depth) {
 if(depth == 0) {
  root->mex = 1;
  return;
 }
 int c = k >> (depth - 1) & 1;
 if(!root->child[c]) root->child[c] = new node();
 insert(root->child[c], k, depth - 1);
 update(root, depth);
 return;
}

node *merging(node *root_a, node *root_b, int depth) {
 if(!root_a) return root_b;
 if(!root_b) return root_a;
 if(depth == -1) return NULL;
 push_down(root_a, depth);
 push_down(root_b, depth);
 node *new_node = new node();
 for(int i = 0; i < 2; i++) {
  new_node->child[i] = merging(root_a->child[i], root_b->child[i], depth - 1);
 }
 update(new_node, depth);
 return new_node;
}

void dfs(int u, int p) {
 int sum_xor = 0;
 for(auto v : g[u]) {
  if(v == p) continue;
  dfs(v, u);
  sum_xor = sum_xor ^ grundy[v];
 }
 root[u] = new node();
 if(!col[u]) {
  insert(root[u], sum_xor, LOG);
 }
 for(auto v : g[u]) {
  if(v == p) continue;
  root[v]->sum_xor = sum_xor ^ grundy[v];
  root[u] = merging(root[u], root[v], LOG);
 }
 grundy[u] = root[u]->mex;
 return;
}

void trace(int u, int p, int sg, vector<int>&ans) {
 int curr_sg = 0;
 for(auto v : g[u]) {
  if(v == p) continue;
  curr_sg = curr_sg ^ grundy[v];
 }
 if(!col[u] && (sg == curr_sg)) ans.push_back(u);
 for(auto v : g[u]) {
  if(v == p) continue;
  trace(v, u, curr_sg ^ grundy[v] ^ sg, ans);
 }
 return;
}

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 cin >> n;
 for(int i = 0; i < n; i++) {
  cin >> col[i];
 }
 for(int i = 0, u, v; i < n - 1; i++) {
  cin >> u >> v;
  --u, --v;
  //cout << u << " " << v << '\n';
  g[u].push_back(v);
  g[v].push_back(u);
 }
 dfs(0, -1);
 vector<int>ans;
 trace(0, -1, 0, ans);
 if(ans.empty()) cout << -1 << '\n', exit(0);
 sort(ans.begin(), ans.end());
 for(auto &x : ans) cout << x + 1 << '\n';
 cout << '\n';
 return 0;
}

/**
 For white node v, the grundy value of the path from 1 to v is
 the mex of grundy value of independent game
 grundy[v] = mex({other white nodes excluded the white nodes on its path})
 
 */
