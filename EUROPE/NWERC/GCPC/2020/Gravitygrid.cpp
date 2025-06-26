#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 3e5 + 10
int h, w, k;    
struct fenwick
{
    int N;
    vector<int>bit; 
    void init(int _N)
    {
         N = _N; 
         bit.resize(N); 
    }
    int sum(int i)
    {
        int c = 0;
        for (++i; i > 0; i -= (i & -i))
        {
            c = c + bit[i];
        }
        return c;
    }
    void upd(int i, int dif)
    {
        for (++i; i < N; i += (i & -i))
        {
            bit[i] = dif + bit[i];
        }
    }
};
fenwick fenw[MAXN];
int ans; 
int hsh(int tx, int ty)
{
     return w * (tx - 1) + ty; 
}  
int fa[MAXN][4]; 
int comp[MAXN][4];
int find(int u, int type)
{
    return u == fa[u][type] ? u : fa[u][type] = find(fa[u][type], type); 
}
void unite(int u, int v, int type)
{
     u = find(u, type);  v = find(v, type);
     if(u == v) return; 
     if(comp[u][type] < comp[v][type]) swap(u, v); 
     comp[u][type] += comp[v][type];
     fa[v][type] = u;
     ans = max(ans, comp[u][type]); 
     return; 
}
int hor[4] = {0, 1, 0, -1}; 
int ver[4] = {1, 0, -1, 0};
int pos[4] = {1, 1, -1, -1};
int neg[4] = {-1, 1, 1, -1};  
signed main(void)
{ 
    scanf("%d %d %d", &h, &w, &k); 
    vector<vector<int> > grid(h + 1, vector<int>(w + 1, -1)); 
    for(int i = 1; i <= w; i++)
    {
         fenw[i].init(h + 1); 
    }
    for(int i = 1; i <= h * w; i++)
    {
         for(int type = 0; type < 4; type++)
         {
             fa[i][type] = i; 
             comp[i][type] = 1; 
         }
    }
    int color = 0;
    ans = 1;
    for(int i = 1; i <= h * w; i++)
    {
         int currw; scanf("%d", &currw); 
         int lo = 1; 
         int hi = h; 
         while(lo < hi)
         {
             int mid = (lo + hi) / 2; 
             if(fenw[currw].sum(mid) == mid)
             {
                 lo = mid + 1; 
             }
             else 
             {
                 hi = mid; 
             }
         }
         if(grid[lo][currw] != -1) continue;
         fenw[currw].upd(lo, 1);
         int tx = lo; int ty = currw;
         grid[tx][ty] = color;
         for(int j = 0; j < 4; j += 2)
         {
             int dx = tx + hor[j];
             int dy = ty + hor[j +  1]; 
             if(1 <= dx && dx <= h && 1 <= dy && dy <= w && grid[dx][dy] == grid[tx][ty])
             {
                 unite(hsh(tx, ty), hsh(dx, dy), 0); 
             }
             dx = tx + ver[j];
             dy = ty + ver[j + 1];
             if (1 <= dx && dx <= h && 1 <= dy && dy <= w && grid[dx][dy] == grid[tx][ty])
             {
                 unite(hsh(tx, ty), hsh(dx, dy), 1);
             }
             dx = tx + pos[j];
             dy = ty + pos[j + 1];
             if (1 <= dx && dx <= h && 1 <= dy && dy <= w && grid[dx][dy] == grid[tx][ty])
             {
                 unite(hsh(tx, ty), hsh(dx, dy), 2);
             }
             dx = tx + neg[j];
             dy = ty + neg[j + 1];
             if (1 <= dx && dx <= h && 1 <= dy && dy <= w && grid[dx][dy] == grid[tx][ty])
             {
                 unite(hsh(tx, ty), hsh(dx, dy), 3);
             }
         }
         if(ans >= k)
         {
             printf("%c %d\n", i & 1 ? 'A' : 'B', i);
             return 0;  
         }
         color = color xor 1; 
    }
    puts("D"); 
    return 0;
}
/* 
    Use segment tree to determine the position that the ball is going to drop
    To check if there is a winner --> use Disjoint set 
    We have four types (horizontal, vertical, diagonal negative, digonal positive) for each cell (can use hash to enumerate the cell)
    if there is a set with size >= k --> the game is finished (the winner is the current player)
    otherwise the game is draw  
*/
