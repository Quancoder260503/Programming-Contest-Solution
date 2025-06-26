#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 100; 

struct node
{
    vector<int>to; 
    void init(int w)
    {
        to.resize(w + 1); 
        for(int i = 1; i <= w; i++) to[i] = i;
        return; 
    }  
};

node tree[maxf];
int N, H, Q;

void add(int p)
{
    for(int i = 1; i <= N; i++)
    {
        tree[p].to[i] = tree[2 * p].to[tree[2 * p + 1].to[i]];
    }
    return; 
}

void build(int l = 1, int r = H, int p = 1)
{
    if(l == r)
    {
        tree[p].init(N); 
        return; 
    }
    int mid = (l + r) / 2; 
    build(l, mid, 2 * p);
    build(mid + 1, r, 2 * p + 1); 
    tree[p].init(N); 
    return; 
}

void update(int pos, int x, int y, int l = 1, int r = H, int p = 1)
{
    if(l == r)
    {
        swap(tree[p].to[x], tree[p].to[y]);
        return; 
    }
    int mid = (l + r) / 2; 
    if(pos <= mid) update(pos, x, y, l, mid, 2 * p); 
    else update(pos, x, y, mid + 1, r, 2 * p + 1); 
    add(p);
    return;  
}

int main(void)
{ 
    cin >> N >> H >> Q;
    build(); 
    for(int i = 0; i < Q; i++)
    {
        int X1, X2, Y; 
        cin >> Y >> X1 >> X2;
        update(Y, X1, X2);
        vector<int>vis(N + 1, 0);
        auto perm = tree[1].to; 
        int ctr = 0;
        for(int j = 1; j <= N; j++)
        {
            if(vis[j]) continue; 
            ctr++; 
            vis[j] = 1;
            int at = j;
            while(!vis[perm[at]])
            {
                at = perm[at]; 
                vis[at] = 1; 
            }
        }
        cout << N - ctr << '\n'; 
    }
    return 0; 
}