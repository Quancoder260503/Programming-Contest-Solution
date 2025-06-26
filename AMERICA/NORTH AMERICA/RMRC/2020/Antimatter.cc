#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 2; 
const int INF = 1e9 + 10; 

int D, S;

pair<int, int> tree[maxf * 4]; 
int ret[maxf]; 
vector<pair<int, int>>g[maxf]; 

void update(int add, int pos, int idx, int val, int l, int r, int p)
{
    if(l == r)
    {
        if(add)
        {
            g[l].push_back({val, idx});
        }
        else if (g[l].size())
        {
            g[l].pop_back();
        }
        tree[p] = (g[l].size() ? make_pair(g[l].back().first, l) : make_pair(INF, -1));
        return; 
    }
    int mid = (l + r) / 2; 
    if(pos <= mid) update(add, pos, idx, val, l, mid, 2 * p); 
    else  update(add, pos, idx, val, mid + 1, r,  2 * p + 1); 
    tree[p] = min(tree[2 * p], tree[2 * p + 1]);
}

pair<int, int> query(int L, int R, int l, int r, int p)
{
    if(L > r || R < l) return {INF, -1}; 
    if(L <= l && r <= R) return tree[p]; 
    int mid = (l + r) / 2; 
    return min(query(L, R, l, mid, 2 * p), query(L, R, mid + 1, r, 2 * p + 1)); 
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> D >> S;
    vector<int>coord;
    coord.push_back(0); 
    coord.push_back(INF); 
    vector<array<int, 4>>seg;  
    for(int i = 0; i < D; i++)
    { 
        int x, y; 
        cin >> x >> y; 
        coord.push_back(x); 
        seg.push_back({y, x, -1, i}); 
    }
    for(int i = 0; i < S; i++)
    {
        int x1, x2, y; 
        cin >> x1 >> x2 >> y; 
        coord.push_back(x1);
        coord.push_back(x2); 
        seg.push_back({y, x1, x2, i}); 
    }
    seg.push_back({0, 0, INF - 2, -1}); 
    sort(coord.begin(), coord.end()); 
    coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
    sort(seg.rbegin(), seg.rend());
    int N = coord.size(); 
    for(int i = 1; i <= N; i++) update(1, i, -1, INF, 1, N, 1); 
    int ctr = 0;
    for(auto [y, x1, x2, idx] : seg)
    {
        if(x2 == -1)
        {
            int pos = lower_bound(coord.begin(), coord.end(), x1) - coord.begin(); 
            update(1, pos, idx, y, 1, N, 1); 
        }
        else
        {
            int L = lower_bound(coord.begin(), coord.end(), x1) - coord.begin();
            int R = lower_bound(coord.begin(), coord.end(), x2) - coord.begin();
            auto curr = query(L, R, 1, N, 1); 
            int str  = curr.first; 
            if(str == INF) continue; 
            while(str == (curr = query(L, R, 1, N, 1)).first)
            {
                if (g[curr.second].size())
                {
                    int u = g[curr.second].back().second;
                    ctr++; 
                    ret[u] = y;  
                }
                update(0, curr.second, -1, INF, 1, N, 1); 
                //if(ctr == 1) break; 
            }
        }
    }
    for(int i = 0; i < D; i++) cout << ret[i] << '\n';
    return 0;
}