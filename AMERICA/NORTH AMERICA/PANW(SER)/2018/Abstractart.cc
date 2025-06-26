#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

bool find(int j, vector<vector<int>> &g, vector<int> &btoa, vector<int> &vis) {
  if (btoa[j] == -1) return 1;
  vis[j] = 1;
  int di = btoa[j];
  for (int e : g[di])
    if (!vis[e] && find(e, g, btoa, vis)) {
      btoa[e] = di;
      return 1;
    }
  return 0;
}
int dfsMatching(vector<vector<int>> &g, vector<int> &btoa) {
  vector<int> vis;
  for (int i = 0; i < sz(g); i++) {
    vis.assign(sz(btoa), 0);
    for (int j : g[i])
      if (find(j, g, btoa, vis)) {
        btoa[j] = i;
        break;
      }
  }
  return sz(btoa) - (int)count(btoa.begin(), btoa.end(), -1);
}

pair<int, vector<int>> min_cover(vector<vector<int>> &g, int n, int m) {
  vector<int> match(m, -1);
  int res = dfsMatching(g, match);
  vector<bool> lfound(n, true), seen(m);
  for (int it : match)
    if (it != -1) lfound[it] = false;
  vector<int> q, cover;
  for (int i = 0; i < n; i++)
    if (lfound[i]) q.push_back(i);
  while (!q.empty()) {
    int i = q.back();
    q.pop_back();
    lfound[i] = 1;
    for (int e : g[i])
      if (!seen[e] && match[e] != -1) {
        seen[e] = true;
        q.push_back(match[e]);
      }
  }
  for (int i = 0; i < n; i++)
    if (!lfound[i]) cover.push_back(i);
  for (int i = 0; i < m; i++)
    if (seen[i]) cover.push_back(i);
  assert(sz(cover) == res);
  return {res, cover};
}

int main(void) {
  int n, m;
  cin >> n >> m;
  vector<vector<char>> g(n, vector<char>(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      cin >> g[i][j];
    }
  vector<vector<int>> adj(n * m), radj(n * m);
  const int dx[4] = {0, 0, -1, 1};
  const int dy[4] = {1, -1, 0, 0};
  auto idx = [&](int i, int j) { return i * m + j; };
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (g[i][j] != '#') {
        if ((i + j) & 1) {
          for (int k = 0; k < 4; k++) {
            int px = i + dx[k], py = j + dy[k];
            if (0 <= px && px < n && 0 <= py && py < m && g[px][py] != '#' &&
                g[px][py] != g[i][j]) {
              adj[idx(i, j)].push_back(idx(px, py));
              radj[idx(px, py)].push_back(idx(i, j));
            }
          }
        }
      }
  auto [ret, cover] = min_cover(adj, n * m, n * m);
  auto [_, rcover] = min_cover(radj, n * m, n * m);
  cout << ret << '\n';
  vector<int> need(n * m, false), marked(n * m, false);
  for (auto x : cover) marked[x] = true;
  for (auto x : rcover)
    if (marked[x]) need[x] = true;
  vector<bool> res(26);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (g[i][j] != '#') {
        if (!need[idx(i, j)]) res[g[i][j] - 'a'] = true;
      }
  for (int i = 0; i < res.size(); i++)
    if (res[i]) cout << char(i + 'a');
  cout << '\n';
  return 0;
}