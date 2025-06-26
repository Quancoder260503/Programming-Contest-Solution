#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define rep(i, j, k) for(int i = j; i < k; i++)

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	vector<int> time, path, ret, depth;
	RMQ<int> rmq;

	LCA(vector<vector<int>>& C) : depth(sz(C)), time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vector<int>>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
            depth[y] = depth[v] + 1; 
			dfs(C, y, v);
		}
	}
	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	int dist(int a, int b){ return depth[a] + depth[b] - 2 * depth[lca(a, b)];}
};
int main(void) { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0); 
    int n, q; 
    cin >> n; 
    vector<vector<int>>g(n); 
    for(int i = 0, u, v; i < n - 1; i++) { 
        cin >> u >> v;
        g[--u].push_back(--v); 
        g[v].push_back(u);
    }
    LCA tree(g); 
    cin >> q; 
    for(int i = 0, k; i < q; i++) { 
        cin >> k; 
        vector<int>a(k); 
        for(int j = 0; j < k; j++) { 
            cin >> a[j]; 
            a[j]--; 
        }
        int64_t ret = 10'000'000'000;
        vector<int>mark(n); 
        for(int x = 0; x < k; x++)
        for(int y = x + 1; y < k; y++) { 
            int anc = tree.lca(a[x], a[y]); 
            if(mark[anc]) continue; 
            int64_t sum = 0; 
            for(int z = 0; z < k; z++) { 
                sum += tree.dist(a[z], anc); 
                if(sum >= ret) break; 
            }
            mark[anc] = true; 
            ret = min(ret, sum); 
        }
        cout << (ret == 10'000'000'000 ? 0 : ret) << '\n'; 
    } 
    return 0;
}

