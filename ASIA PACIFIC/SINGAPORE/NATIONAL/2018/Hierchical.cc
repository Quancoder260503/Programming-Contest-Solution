#include "bits/stdc++.h"

using namespace std; 

#define sz(x) (int) x.size()

struct node { 
    node* L; 
    node* R; 
    int64_t val;
    node(int64_t _val, node* _L, node* _R) { 
        L = _L, R = _R; 
        val = _val; 
    } 
};

const int maxf = 1e5 + 10; 
const int LOG = 23; 

node* root[maxf];  
int up[LOG][maxf], a[maxf], depth[maxf]; 
vector<int>g[maxf]; 
vector<int>coord;
map<int, int>rec; 

node *build(int L, int R) { 
    if(L == R) return new node(0, NULL, NULL);
    int mid = (L + R) / 2; 
    return new node(0, build(L, mid), build(mid + 1, R)); 
}

node *build(int pos, int L, int R, int64_t v, node *pre) { 
    if(pos < L || pos > R) return pre; 
    if(L == R) return new node(pre->val + v, NULL, NULL);
    int mid = (L + R) / 2; 
    node* cc = new node(0, NULL, NULL); 
    cc->L = build(pos, L, mid, v, pre->L);
    cc->R = build(pos, mid + 1, R, v, pre->R);
    cc->val = cc->L->val + cc->R->val; 
    return cc;   
}

int64_t query(int L, int R, int x, int y, node *now) { 
    if(y < L || R < x) return 0; 
    if(x <= L && R <= y) return now->val; 
    int mid = (L + R) / 2; 
    int64_t ret = 0; 
    if(now->L) ret += query(L, mid, x, y, now->L);
    if(now->R) ret += query(mid + 1, R, x, y, now->R); 
    return ret; 
}

void dfs(int u, int p) {
    if(u) root[u] = build(rec[a[u]], 0, sz(coord) - 1, a[u], root[p]);  
    for(int i = 1; i < LOG; i++) { 
        up[i][u] = up[i - 1][up[i - 1][u]]; 
    } 
    for(auto v : g[u]) if(v != p) { 
        up[0][v] = u; 
        depth[v] = depth[u] + 1; 
        dfs(v, u); 
    }
    return; 
}

int LCA(int u, int v) { 
    if(depth[u] < depth[v]) swap(u, v); 
    int dist = depth[u] - depth[v]; 
    for(int i = 0; i < LOG; i++) { 
        if(dist & (1 << i)) u = up[i][u]; 
    }
    if(u == v) return u; 
    for(int i = LOG - 1; i >= 0; i--) { 
        int du = up[i][u], dv = up[i][v]; 
        if(du != dv) { 
            u = du, v = dv; 
        }
    }
    return up[0][u]; 
}

int main(void) {
    int n, q; 
    cin >> n >> q; 
    for(int i = 0; i < n; i++) { 
        cin >> a[i];    
        coord.push_back(a[i]); 
    }
    sort(coord.begin(), coord.end());
    coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
    for(int i = 0; i < n; i++) { 
        rec[a[i]] = lower_bound(coord.begin(), coord.end(), a[i]) - coord.begin(); 
    }
    node* start = build(0, sz(coord)); 
    root[0] = build(rec[a[0]], 0, sz(coord), a[0], start); 
    for(int i = 0; i < n - 1; i++) { 
        int u, v; 
        cin >> u >> v;
        g[--u].push_back(--v);
        g[v].push_back(u); 
    }
    dfs(0, -1); 
    for(int i = 0; i < q; i++) {
        int l, r, x, y; 
        cin >> x >> y >> l >> r;
        l = lower_bound(coord.begin(), coord.end(), l) - coord.begin(); 
        r = upper_bound(coord.begin(), coord.end(), r) - coord.begin() - 1; 
        if(l > r) { 
            cout << 0 << '\n'; 
            continue; 
        } 
        --x, --y; 
        int anc = LCA(x, y); 
        int64_t ret = query(0, sz(coord) - 1, l, r, root[x]) + query(0, sz(coord) - 1, l, r, root[y]);
        ret -= 2 * query(0, sz(coord) - 1, l, r, root[anc]);
        ret += (l <= rec[a[anc]] && rec[a[anc]] <= r ? a[anc] : 0); 
        cout << ret << '\n';  
    }
    return 0; 
}