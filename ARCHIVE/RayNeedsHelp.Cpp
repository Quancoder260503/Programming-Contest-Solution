#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 5;
const long long INF = 1e19 - 1;
const int mod = 1e9 + 7; 
long long n,m,k,q;
long long a[N + 1]; 
int in[N + 1];
int out[N + 1];
int dp[N + 1];
int timer = 1; 
using type = long long; 
struct Matrix {
    vector <vector <type> > data;
 
    int row() const { return data.size(); } 
    int col() const { return data[0].size(); }
    auto & operator [] (int i) { return data[i]; }   
    const auto & operator[] (int i) const { return data[i]; }
    Matrix() = default;
    
    Matrix(int r, int c): data(r, vector <type> (c)) { }
 
    Matrix(const vector <vector <type> > &d): data(d) {
        assert(d.size());
        int size = d[0].size();
        assert(size);
        for (auto x : d) assert(x.size() == size);
    }
    Matrix operator * (const Matrix &b) {
        Matrix a = *this;
        assert(a.col() == b.row()); 
        Matrix c(a.row(), b.col());
        for (int i = 0; i < a.row(); ++i){
            for (int j = 0; j < b.col(); ++j){
                c[i][j] = INF;
                for (int k = 0; k < a.col(); ++k){
                    if(a[i][k] >= INF or b[k][j] >= INF or a[i][k] + b[k][j] >= INF) continue;
                    c[i][j] = min(c[i][j], a[i][k] + b[k][j]);
                }
            }
        }
        return c;
    }
};
int main(){
     scanf("%lld%lld%lld",&n,&m,&q); 
     Matrix adj(n,n);
     for(int i = 0; i < n; i++){
         for(int j = 0; j < n; j++){
             adj[i][j] = INF;
         }
     }
     Matrix infy = adj;
     for(int i = 1; i <= m; i++){
            long long u,v,w; scanf("%d%d%lld",&u,&v,&w);
            adj[u - 1][v - 1] = min(w,adj[u - 1][v - 1]); 
     }
     Matrix tadj[30];
     tadj[0] = adj; 
     for(int i = 1; i < 30; i++) tadj[i] = tadj[i - 1] * tadj[i - 1]; 
     for(int i = 0; i < q; i++){ 
        int u,v; long long k; scanf("%d%d%lld",&u,&v,&k);
        Matrix res = infy;
        res[0][u - 1] = 0; 
        int pow = 0; 
        while(k){
             if(k & 1) res = res * tadj[pow]; 
             k = k / 2; 
             pow++; 
        }
        long long val = res[0][v - 1];
        long long ans = val == INF ? -1 : val;
        cout<<ans<<endl; 
     }
     return 0; 
}