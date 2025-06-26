#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 2e6 + 5
long long dist[MAXN];
int A[MAXN]; 
int vis[MAXN]; 
int n; 
long long k; 
void bfs()
{
    memset(dist,0x3f,sizeof(dist));
    dist[0] = 0; 
    queue<int>q; 
    q.push(0);
    while(q.size())
    {
         int u = q.front(); 
         q.pop();
         for(int i = 2; i <= n; i++)
         { 
             if(dist[((u + A[i]) % A[1])] > dist[u] + A[i])
             {
                 dist[(u + A[i]) % A[1]] = dist[u] + A[i]; 
                 if(!vis[(u + A[i]) % A[1]])
                 {
                     vis[(u + A[i]) % A[1]] = 1; 
                     q.push((u + A[i]) % A[1]); 
                 }
             }
         }
    }
    return; 
}
signed main(void)
{
     scanf("%d%lld",&n,&k);
     for(int i = 1; i <= n; i++)
     {
          scanf("%d",&A[i]); 
     }
     sort(A + 1, A + n + 1);
     bfs();
     if(k >= dist[k % A[1]])
     {
         puts("possible"); 
     }
     else
     {
         puts("impossible"); 
     }
     return 0;
}

/*2 10000000000 4 6*/