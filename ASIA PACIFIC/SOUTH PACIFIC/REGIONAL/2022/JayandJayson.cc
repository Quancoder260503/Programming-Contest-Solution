#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int maxn = 2e5 + 10;
const int LOG = 19;

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
int n, grundy[maxn];

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
 insert(root[u], sum_xor, LOG);
 for(auto v : g[u]) {
  if(v == p) continue;
  root[v]->sum_xor = sum_xor ^ grundy[v];
  root[u] = merging(root[u], root[v], LOG);
 }
 grundy[u] = root[u]->mex;
 return;
}

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 cin >> n;
 for(int i = 1, par; i <= n; i++) {
  cin >> par;
  g[par].push_back(i);
 }
 int ans = 0;
 for(auto v : g[0]) {
  dfs(v, -1);
  ans = ans ^ grundy[v];
 }
 cout << (!ans ? "ja$on" : "Jay") << '\n';
 return 0;
}

