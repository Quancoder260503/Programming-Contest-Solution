#include "bits/stdc++.h"
using namespace std;
#define inf 1000000000000000
#define mp make_pair
int n,m;
struct Dinic{ 
    struct Edge{
        int to;
        long long flow,cap; 
        Edge(int _to,long long _flow,long long _cap): to(_to), flow(_flow), cap(_cap) {}
    };
    int N; 
    vector<Edge>edges; 
    vector<vector<int> >adj; 
    vector<vector<int> :: iterator > cur; 
    void init(int _N){
         N = _N; 
         adj.resize(N); 
         cur.resize(N); 
    }
    vector<int>dist;
    void conn(int u,int v,long long flow){
        adj[u].push_back(edges.size()); 
        edges.push_back(Edge(v,0,flow));
        adj[v].push_back(edges.size()); 
        edges.push_back(Edge(u,0,0));  
    }
    bool bfs(int s, int t){
        dist = vector<int>(N,-1);
        queue<int>q; 
        q.push(s); 
        dist[s] = 0;
        for(int i = 0; i < N; i++) cur[i] = adj[i].begin(); 
        while(q.size()){
            int node = q.front();
            q.pop(); 
            for(int i = 0; i < adj[node].size(); i++){
                const Edge &E = edges[adj[node][i]]; 
                int v = E.to;
                if(dist[v] < 0 && E.flow < E.cap){
                     dist[v] = dist[node] + 1;
                     q.push(v); 
                }
            }
        }
        return dist[t] + 1 > 0; 
    }
    long long dfs(int s, int t, long long flow){
        if(s == t) return flow;    
        for(;cur[s] != adj[s].end(); cur[s]++){
              Edge &E = edges[*cur[s]]; 
              if(dist[E.to] != dist[s] + 1 || E.flow == E.cap) continue; 
              long long df = dfs(E.to,t,min(flow,E.cap - E.flow)); 
              if(df){
                  E.flow += df;
                  edges[*cur[s] xor 1].flow -= df;
                  return df;
              }
        }
        return 0;       
    }
    long long maxflow(int s, int t){
         long long ans = 0;
         while(bfs(s,t)){
              while(long long df = dfs(s,t,inf)) ans += df;
         }
         return ans;
    }
};
signed main(){ 
    scanf("%d%d",&n,&m);
    Dinic Di; 
    Di.init(n + 1);  
    vector<pair<int,int> >eds;
    for(int i = 0; i < m; i++){
         int u,v; scanf("%d%d",&u,&v);
         //if(u > v) swap(u,v);
         eds.push_back(mp(u,v)); 
         Di.conn(u,v,1);
         Di.conn(v,u,1);
    }
    printf("%lld\n",Di.maxflow(1,n)); 
    Di.bfs(1,n);
    for(int i = 0; i < eds.size(); i++){
         int u = eds[i].first;
         int v = eds[i].second;
         if(Di.dist[u] >= 0 && Di.dist[v] < 0){
             printf("%d %d\n",u,v); 
             continue; 
         }
         if(Di.dist[v] >= 0 && Di.dist[u] < 0){
            printf("%d %d\n",u,v); 
         }
    } 
    return 0;
}