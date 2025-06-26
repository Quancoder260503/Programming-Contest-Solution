#include "bits/stdc++.h"
using namespace std;
#define inf 1000000000000000
#define MAX 1000005
using vec = pair<int,int>; 
#define mp make_pair
int n,m;
struct Vec {
    long long x, y;
    Vec(long long _x = 0, long long _y = 0) : x(_x), y(_y) {}
    long long dot(const Vec &other) {
        return x * other.x + y * other.y;
    }
    long long cross(const Vec &other) {
        return 1ll * x * other.y - 1ll * y * other.x;
    }
    long long length() const {
        return sqrt(x * x + y * y);
    }
};
using Point = Vec;
Vec operator - (const Point &B, const Point &A) { 
    return Vec(B.x - A.x, B.y - A.y);
}
int sign(long long x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}
long long cross(Vec AB, Vec AC) {
    return AB.x * AC.y - AC.x * AB.y;
}
long long dot(Vec AB, Vec AC) {
    return AB.x * AC.x + AB.y * AC.y;
}
bool intersect(Point A, Point B, Point C, Point D) {
    int ABxAC = sign(cross(B - A, C - A));
    int ABxAD = sign(cross(B - A, D - A));
    int CDxCA = sign(cross(D - C, A - C));
    int CDxCB = sign(cross(D - C, B - C));
    if (ABxAC == 0 || ABxAD == 0 || CDxCA == 0 || CDxCB == 0) {
        if (ABxAC == 0 && sign(dot(A - C, B - C)) <= 0) return true;
        if (ABxAD == 0 && sign(dot(A - D, B - D)) <= 0) return true;
        if (CDxCA == 0 && sign(dot(C - A, D - A)) <= 0) return true;
        if (CDxCB == 0 && sign(dot(C - B, D - B)) <= 0) return true;
        return false;
    }
    return (ABxAC * ABxAD < 0 && CDxCA * CDxCB < 0);
}
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
struct line{
     Point A,B; 
} lines[MAX]; 
signed main(){ 
    scanf("%d",&n);
    Dinic Di; 
    Di.init(n + 2);  
    for(int i = 1; i <= n; i++){
         scanf("%d%d%d%d",&lines[i].A.x,&lines[i].A.y,&lines[i].B.x,&lines[i].B.y);
    }
    vector<line>hori; 
    vector<line>vert;
    for(int i = 1; i <= n; i++){
          if(lines[i].A.x == lines[i].B.x){
              Di.conn(0, i, 1); 
              vert.push_back(lines[i]); 
          }
          if(lines[i].A.y == lines[i].B.y){ 
              Di.conn(i, n + 1, 1); 
              hori.push_back(lines[i]); 
          }
    }
    for(int i = 1; i <= n; i++){
        if(lines[i].A.x == lines[i].B.x){
           for(int j = 1; j <= n; j++){
               if(i == j) continue;
               if(intersect(lines[i].A,lines[i].B,lines[j].A,lines[j].B)){
                  Di.conn(i, j, 1); 
               }
            }
        } 
    }
    printf("%lld\n", n - Di.maxflow(0,n + 1)); 
    return 0;
}