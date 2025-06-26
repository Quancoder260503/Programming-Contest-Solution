#include "bits/stdc++.h"

using namespace std;

const int maxf = 5e5 + 10;
const int INF = 1e9; 

struct node { 
    int64_t x, y;
    node operator + (const node &b) { 
        return {max(x + 2 * b.y, b.x), y + b.y}; 
    }
};

node tree[maxf << 2];
int n;

void update(int pos, node val, int l = 0, int r = n, int p = 1) { 
    if(l == r) {
        tree[p].x = val.x; tree[p].y = val.y;  
        return; 
    }
    int mid = (l + r) / 2; 
    if(pos <= mid) update(pos, val, l, mid, 2 * p); 
    else update(pos, val, mid + 1, r, 2 * p + 1); 
    tree[p] = tree[2 * p] + tree[2 * p + 1];
    return; 
}

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> n;
    vector<pair<int, int>>pts; 
    node c;
    for(int i = 0, x; i <= n; i++) {
        update(i, {-INF, 0});
        cin >> x;
        pts.push_back({x, i});
    }
    sort(pts.begin(), pts.end());
    vector<int>vis(pts.size()); 
    int64_t ret = 0, ptr = 0; 
    for(int i = 0; i < pts.size(); i++) {
        update(pts[i].second, {pts[i].second + (pts[i].second % 2 == 0), 1});
        vis[pts[i].second] = 1;  
        while(ptr < pts.size() && vis[ptr]) {
            update(ptr, {-INF, 0}); 
            ptr++; 
        }
        ret = max(ret, tree[1].x - i); 
    }
    cout << ret << '\n'; 
    return 0;
}