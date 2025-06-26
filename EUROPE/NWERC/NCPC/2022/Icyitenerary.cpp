#include "bits/stdc++.h"
using namespace std;
#define N 1000005
#define mp make_pair
int n, m;
set<int> adj[N];
set<int> vset;
vector<int> res;
int vis[N];
int fa[N];
int dep[N];
vector<int>white,black; 
signed main(void)
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].insert(v);
        adj[v].insert(u);
    }
    for (int i = 2; i <= n; i++)
    {
        vset.insert(i);
    }
    if(adj[1].size())
    {
        white.push_back(*adj[1].begin()); 
        vset.erase(*adj[1].begin()); 
    }
    else
    {
        black.push_back(2);
        vset.erase(2);  
    }
    while(vset.size())
    {
        while(white.size())
        {
           int curr = white.back();
           for(auto u : adj[curr])
           {
               if(vset.count(u))
               {
                   vset.erase(u); 
                   white.push_back(u); 
                   break; 
               }
           }
           if(curr == white.back()) break; 
        }
        if (!vset.size()) break;
        if(!black.size())
        {
             black.push_back(*vset.begin()); 
             vset.erase(*vset.begin());  
        }
        while(black.size())
        {
             int curr = black.back();
             int nxt = -1;
             for(auto it = vset.begin(); it != vset.end(); it++)
             {
                  if(!adj[curr].count(*it))
                  {
                     black.push_back(*it); 
                     nxt = *it; 
                     break;   
                  }
             }
             if(nxt != -1)
             {
                 vset.erase(nxt); 
             }
             if (curr == black.back()) break;
        }
        if(!vset.size()) break; 
        if(!white.size())
        {
             white.push_back(*vset.begin());
             vset.erase(*vset.begin());
        }
        int bwhite = white.back();
        int bblack = black.back(); 
        if(adj[bwhite].count(bblack))
        {
             white.push_back(bblack);
             black.pop_back(); 
        }
        else
        {
             white.pop_back(); 
             black.push_back(bwhite); 
        }
    }
    printf("1 "); 
    if(!m)
    {
         for(auto it = black.begin(); it != black.end(); it++)
         {
             printf("%d ", *it); 
         }
    }
    else{
         if (black.size() && !adj[1].count(black[0]))
         {
             for (auto it = black.begin(); it != black.end(); it++)
             {
                 printf("%d ", *it);
             }
             for (auto it = white.begin(); it != white.end(); it++)
             {
                 printf("%d ", *it);
             }
         }
         else
         {
             for (auto it = white.begin(); it != white.end(); it++)
             {
                 printf("%d ", *it);
             }
             for (auto it = black.begin(); it != black.end(); it++)
             {
                 printf("%d ", *it);
             }
         }
    }
    return 0;
}