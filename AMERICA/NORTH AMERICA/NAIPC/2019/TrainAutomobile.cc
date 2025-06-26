#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()

bool dfs(int a, int L, vector<vector<int>>& g, vector<int>& btoa, vector<int>& A, vector<int>& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	for (int b : g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vector<vector<int>>& g, vector<int>& btoa) {
	int res = 0;
	vector<int> A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(all(A), 0);
		fill(all(B), 0);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		for (int a : btoa) if(a != -1) A[a] = -1;
		for(int a = 0; a < sz(g); a++) if(A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			for (int a : cur) for (int b : g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			for (int a : next) A[a] = lay;
			cur.swap(next);
		}
		for(int a = 0; a < sz(g); a++) {  
			res += dfs(a, 0, g, btoa, A, B);
        }
	}
    return res;  
}

pair<int, vector<int>> doit(vector<vector<int>>& g, int n) {
	vector<int> match(n, -1);
	int ans = hopcroftKarp(g, match);
    vector<int>lfound(n, true), seen(n), q; 
    for(auto it : match) if(it != -1) lfound[it] = false;
	for(int i = 0; i < n; i++) if (lfound[i]) { 
        seen[i] = true; 
        q.push_back(i); 
    }
	while (!q.empty()) {
		int i = q.back(); q.pop_back();
		for (int e : g[i]) if (match[e] != -1 && !seen[match[e]]) {
		    seen[match[e]] = true;
			q.push_back(match[e]);
		}
	} 
    vector<int>ret; 
    for(int i = 0; i < n; i++) {
        if(seen[i] || match[i] == -1) ret.push_back(i + 1); 
    }
	return {ans, ret};
}

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int n, m; 
    cin >> n >> m; 
    vector<vector<int>>g(n), rg(n);
    for(int i = 0, u, v; i < m; i++) { 
        cin >> u >> v; 
        g[--u].push_back(--v);
        rg[v].push_back(u); 
    }
    auto [ret, citya] = doit(g,  n);
    auto [_  , cityb] = doit(rg, n); 
    ret = n - 1 - ret; 
    cout << ret << '\n'; 
    if(ret) { 
       vector<int>mark(n + 1); 
       for(auto &x : citya) mark[x] = true; 
       for(auto &x : cityb) mark[x] = true; 
       for(int i = 1; i <= n; i++) if(mark[i]) {
          cout << i << " ";  
       }
       cout << '\n'; 
    }
    return 0; 
} 