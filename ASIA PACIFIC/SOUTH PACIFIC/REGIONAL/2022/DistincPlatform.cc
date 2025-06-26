#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxf = 1e6; 
const int INF = 1e9 + 10; 

pair<int, int>tree[maxf << 2]; 
set<pair<int, int>>ms[maxf << 2]; 

void init(int l, int r, int p = 1) { 
    if(l == r) {
        tree[p] = {INF, INF}; 
        return; 
    } 
    int mid = (l + r) / 2; 
    init(l, mid, 2 * p); 
    init(mid + 1, r, 2 * p + 1);
    tree[p] = {INF, INF}; 
    return; 
}

void update(int id, int val, int pos, int l, int r, int p = 1) { 
    if(l == r) {
        if(id == -1) { 
            ms[p].erase(tree[p]); 
        }
        else { 
            ms[p].insert({val, id}); 
        }
        tree[p] = (sz(ms[p]) ? (*ms[p].begin()) : make_pair(INF, INF));  
        return; 
    }
    int mid = (l + r) / 2; 
    if(pos <= mid) update(id, val, pos, l, mid, 2 * p);
    else           update(id, val, pos, mid + 1, r, 2 * p + 1);
    tree[p] = min(tree[2 * p], tree[2 * p + 1]); 
    return; 
}

pair<int, int> query(int L, int R, int l, int r, int p = 1) { 
    if(L > r || R < l)  return {INF, INF}; 
    if(L <= l && r <= R) return tree[p]; 
    int mid = (l + r) / 2; 
    return min(query(L, R, l, mid, 2 * p), query(L, R, mid + 1, r, 2 * p + 1)); 
}

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n; 
    vector<int>coord{0}, l(n), r(n), L(n), R(n); 
    for(int i = 0; i < n; i++) { 
        cin >> l[i] >> r[i]; 
        L[i] = l[i], R[i] = r[i]; 
        coord.push_back(l[i]); 
        coord.push_back(r[i]); 
    }
    sort(coord.begin(), coord.end()); 
    coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
    vector<int>ord(n);
    iota(ord.begin(), ord.end(), 0); 
    init(1, sz(coord) - 1); 
    for(int i = 0; i < n; i++) {
        l[i] = lower_bound(coord.begin(), coord.end(), l[i]) - coord.begin();
        r[i] = lower_bound(coord.begin(), coord.end(), r[i]) - coord.begin(); 
        update(i, r[i], l[i], 1, sz(coord) - 1); 
    } 
    sort(ord.begin(), ord.end(), [&](int i, int j) { 
        return r[i] == r[j] ? l[i] > l[j] : r[i] < r[j]; 
    }); 
    vector<int>ret{ord.front()};
    int curr = ret.back();  
    vector<int>visited(n); 
    for(int i = 1; i < n; i++) {
        update(-1, -1, l[curr], 1, sz(coord) - 1);
        visited[curr] = true;  
        auto nxt = query(1, r[curr], 1, sz(coord) - 1, 1); 
        if(nxt.first == INF) { 
            cout << "NO\n";
            exit(0);
        } 
        ret.push_back(nxt.second); 
        curr = ret.back();
    }
    visited[curr] = true; 
    assert(count(visited.begin(), visited.end(), true) == n); 
    cout << "YES\n"; 
    for(int i = 0; i < n; i++) { 
        if(i + 1 < n) { 
            int x = ret[i], y = ret[i + 1]; 
            assert((L[x] <= L[y] && L[y] <= R[x]) | (L[x] <= R[y] && R[y] <= R[x]) 
                   | (L[y] <= L[x] && L[x] <= R[y]) | (L[y] <= R[x] && R[x] <= L[y])); 
        }
        cout << ret[i] + 1 << " "; 
    }
    cout << '\n'; 
    return 0; 
}

/*
   Note the prog4fun site doesnt allow multiple solutions juding, hence 
   the solution is not completely judged. 
*/