#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e6 + 10
#define block 388
#define lint long long
#define mp make_pair
#define pii pair<int,int>
int n, q;
const int mod = 998244353; 
int in[MAXN], out[MAXN];
vector<int>adj[MAXN]; 
int deg[MAXN];
int trs[MAXN]; 
int heavy[MAXN]; 
int timer = 1;
int fa[MAXN]; 
int top[MAXN]; 
lint add[MAXN]; 
lint binpow(lint base, int pow)
{
      lint ans = 1; 
      while(pow)
      {
           if(pow & 1) ans = ans % mod * base % mod;
           base = base % mod * base % mod; 
           pow = pow / 2; 
      }
      return ans;
}
struct fenwick
{
     lint bit[MAXN];
     lint query(int i)
     {
          lint c = 0;
          for (++i; i > 0; i -= (i & -i))
          {
               c = (c + bit[i] + mod) % mod;
          }
          return c;
     }
     void upd(int i, lint dif)
     {
          for (++i; i < MAXN; i += (i & -i))
          {
               bit[i] = (dif + bit[i] + mod) % mod;
          }
     }
}fenw; 
void dfs(int u, int p)
{
      in[u] = timer++; 
      trs[u] = 1; 
      for(int i = 0; i < adj[u].size(); i++)
      {
           int v = adj[u][i];
           if(v == p) continue;
           dfs(v, fa[v] = u);
           trs[u] += trs[v];  
      }
      out[u] = timer - 1;
      pii ans = mp(-1, 0);
      for(int i = 0; i < adj[u].size(); i++)
      {
           int v = adj[u][i]; 
           if(v == p) continue; 
           ans = max(ans, mp(trs[v], v)); 
      }
      heavy[u] = ans.second; 
      return; 
}
void dfs2(int u, int p, int id)
{
      top[u] = id;
      if(heavy[u])
      {
          top[heavy[u]] = id; 
          dfs2(heavy[u], u, id); 
      } 
      for(int i = 0; i < adj[u].size(); i++)
      {
           int v = adj[u][i];
           if(v == p || v == heavy[u]) continue;
           dfs2(v, u, v); 
      }
      return; 
}
signed main(void)
{
     scanf("%d %d", &n, &q);
     for(int i = 0; i < n - 1; i++)
     {
           int u, v; 
           scanf("%d %d", &u, &v);
           adj[u].push_back(v);
           adj[v].push_back(u);  
     }
     dfs(1, 0);
     dfs2(1, 0, 1); 
     lint inv = binpow(n, mod - 2);  
     for(int i = 0; i < q; i++)
     {
           int type; scanf("%d", &type);
           if(type == 1)
           {
               int u, dist; 
               scanf("%d %d", &u, &dist); 
               if(heavy[u])
               {
                    int v = heavy[u]; 
                    fenw.upd(in[v], 1LL * inv % mod * dist % mod * (n - trs[v])); 
                    fenw.upd(out[v] + 1, 1LL * inv % mod * dist % mod * (trs[v] - n)); 
               }
               fenw.upd(1, 1LL * inv % mod * dist % mod * trs[u] % mod);
               fenw.upd(in[u], -1LL * inv % mod * dist % mod * trs[u] % mod); 
               fenw.upd(out[u] + 1, 1LL * inv % mod * dist % mod * trs[u] % mod); 
               add[u] = (add[u] + mod + dist % mod * inv % mod) % mod;
           }
           else
           {
               int u;
               scanf("%d", &u);
               lint ans = (fenw.query(in[u]) + 1LL * add[u] % mod * n % mod + mod) % mod;
               int curr = top[u];
               for(int fcurr = fa[curr]; fcurr; fcurr = fa[curr])
               {
                    ans = (ans + mod + 1LL * add[fcurr] % mod * (n - trs[curr]) % mod) % mod; 
                    curr = top[fcurr]; 
               }
               printf("%lld\n", ans) ;
           }
     }
     return 0; 
}