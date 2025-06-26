#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 2e6 + 10
#define M (int) 5e5 + 2
#define pii pair<int,int>
#define mp make_pair 
int n, k;
int ST[MAXN]; 
int LZ[MAXN];
void push_down(int p)
{
     if(LZ[p] != 0)
     {
          LZ[2 * p] += LZ[p];
          LZ[2 * p + 1] += LZ[p]; 
          ST[2 * p] += LZ[p]; 
          ST[2 * p + 1] += LZ[p]; 
          LZ[p] = 0; 
     }
     return; 
}
void update(int val, int L, int R, int l = 1, int r = M, int p = 1)
{
    if(L > r || R < l) return; 
    if(L <= l && r <= R)
    {
         ST[p] += val;
         LZ[p] += val; 
         return; 
    }
    int mid = (l + r) >> 1;
    push_down(p);
    update(val, L, R, l, mid, 2 * p);
    update(val, L, R, mid + 1, r, 2 * p + 1);  
    ST[p] = max(ST[2 * p], ST[2 * p + 1]); 
}
/*
int query(int L, int R, int l = 1, int r = M, int p = 1)
{
    if (L > r || R < l) return 0;
    if (L <= l && r <= R)
    {
      return ST[p]; 
    }
    int mid = (l + r) >> 1;
    push_down(p, l, mid, r);
    return max(query(L, R, l, mid, 2 * p), query(L, R, mid + 1, r, 2 * p + 1)); 
}
*/ 

struct Query 
{ 
     int x, l, r, type; 
     Query(int _x, int _l, int _r, int _type): x(_x), l(_l), r(_r), type(_type) {};  
}; 
vector<Query>Point;
bool cmp(const Query &a, const Query &b)
{
   return a.x == b.x ? a.type < b.type : a.x < b.x;       
}
signed main(void)
{ 
     scanf("%d %d", &n, &k); 
     vector<int>cor;
     for(int i = 1; i <= n; i++)
     {
          int x, y; 
          scanf("%d %d", &x, &y); 
          int tx = x; int ty = y; 
          x = tx + ty; 
          y = tx - ty;
          Point.push_back(Query(x, y, y + 2 * k, 1));
          Point.push_back(Query(x + 2 * k + 1, y, y + 2 * k, -1)); 
          cor.push_back(y);
          cor.push_back(y + 2 * k); 
     }
     sort(cor.begin(), cor.end()); 
     cor.erase(unique(cor.begin(), cor.end()), cor.end()); 
     sort(Point.begin(), Point.end(), cmp); 
     int ans = 0;
     for(int i = 0; i < Point.size(); i++)
     {
          Point[i].l = lower_bound(cor.begin(), cor.end(), Point[i].l) - cor.begin() + 1;
          Point[i].r = lower_bound(cor.begin(), cor.end(), Point[i].r) - cor.begin() + 1; 
          update(Point[i].type, Point[i].l, Point[i].r);
          ans = max(ans, ST[1]);  
     }
     printf("%d\n", ans); 
     return 0; 
}