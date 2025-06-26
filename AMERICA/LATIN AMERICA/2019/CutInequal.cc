#include "bits/stdc++.h"

using namespace std;
const int maxf = 1e5 + 2; 
const int64_t INF = 1e12; 

struct node 
{
    int64_t lo, hi, x;
    node(int64_t _x = 0, int64_t _lo = -INF, int64_t _hi = INF) : x(_x), lo(_lo), hi(_hi) {}; 
};  

node operator + (const node &a, const node &b)
{
    int64_t currL = a.lo + b.x; 
    int64_t currR = a.hi + b.x; 
    if(currR <= b.lo)      return node(a.x + b.x, b.lo, b.lo);
    else if(currL >= b.hi) return node(a.x + b.x, b.hi, b.hi); 
    else return node(a.x + b.x, max(currL, b.lo), min(currR, b.hi));  
}

node tree[maxf * 4]; 
int arr[maxf]; 
int64_t N, Q, L, R; 

void build(int l = 1, int r = N, int p = 1)
{
    if(l == r)
    {
        tree[p] = node(arr[l], L, R); 
        return; 
    }
    int mid = (l + r) / 2; 
    build(l, mid, 2 * p);
    build(mid + 1, r, 2 * p + 1);
    tree[p] = tree[2 * p] + tree[2 * p + 1]; 
    return; 
}

node null = node(); 

node query(int lb, int rb, int l = 1, int r = N, int p = 1)
{
    if(lb > r || rb < l) return null;
    if(lb <= l && r <= rb) return tree[p]; 
    int mid = (l + r) / 2; 
    return query(lb, rb, l, mid, 2 * p) + query(lb, rb, mid + 1, r, 2 * p + 1); 
}

int main(void)
{
    while(cin >> N >> L >> R)
    {
        for(int i = 1; i <= N; i++) cin >> arr[i]; 
        build(); 
        cin >> Q; 
        for(int i = 0; i < Q; i++)
        {
            int l, r; 
            int64_t x; 
            cin >> l >> r >> x;
            auto ret = query(l, r);           
            ret.x += x; 
            ret.x = max(ret.x, ret.lo); 
            ret.x = min(ret.x, ret.hi); 
            cout << ret.x << '\n';
        }
        return 0; 
    }
    return 0;
}