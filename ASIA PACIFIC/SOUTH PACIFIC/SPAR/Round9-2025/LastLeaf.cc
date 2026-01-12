#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <cstring> 

using namespace std;

#define ll long long

const int oo = 1e9;
const int maxn = 5e5 + 10;

vector<int>g[maxn];
int n, k, depth[maxn], marked[maxn];

void dfs(int u, int p) {
 for(auto v : g[u]) {
  if(v == p) continue;
  depth[v] = depth[u] + 1;
  dfs(v, u);
 }
 return;
}

int dfs2(int u, int p) {
 int ret = 0;
 for(auto v : g[u]) {
  if(v == p) continue;
  ret = max(ret, dfs2(v, u));
 }
 //cout << u << " " << marked[u] << '\n';
 return marked[u] ? -oo : 1 + ret;
}

void solve() {
 cin >> n >> k;
 for(int i = 0; i < n; i++) {
  g[i].clear();
  depth[i] = 0;
  marked[i] = 0;
 }
 for(int i = 0, u, v; i < n - 1; i++) {
  cin >> u >> v;
  --u, --v;
  g[u].push_back(v);
  g[v].push_back(u);
 }
 dfs(0, -1);
 vector<int>ord(n);
 iota(ord.begin(), ord.end(), 0);
 sort(ord.begin(), ord.end(), [&](int i, int j) {
   return depth[i] > depth[j];
 });
 for(int i = 0; i < k; i++) {
 // cout << ord[i] << '\n';
  marked[ord[i]] = 1;
 }
 cout << dfs2(0, -1) << '\n';
 return;
}

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 int C;
 for(cin >> C; C--; ) solve();
 return 0;
}
