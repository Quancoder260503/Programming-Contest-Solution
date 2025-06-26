#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 5;
const int INF = 1e16 + 5;
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
    friend ostream & operator << (ostream &out, const Matrix &d) {
        for (auto x : d.data) {
            for (auto y : x) out << y << ' ';
            out << '\n';
        }
        return out;
    }
    static Matrix identity(long long n) {
        Matrix a = Matrix(n, n);
        while (n--) a[n][n] = 1;
        return a;
    }
    Matrix operator * (const Matrix &b) {
        Matrix a = *this;
        assert(a.col() == b.row()); 
 
        Matrix c(a.row(), b.col());
        for (int i = 0; i < a.row(); ++i)
            for (int j = 0; j < b.col(); ++j)
                for (int k = 0; k < a.col(); ++k)
                    c[i][j] = (c[i][j] + mod + a[i][k] % mod * b[k][j] % mod) % mod;
        return c;
    }
    Matrix pow(long long exp) {
        assert(row() == col());  
        Matrix base = *this, ans = identity(row());
        for (; exp > 0; exp >>= 1, base = base * base)
            if (exp & 1) ans = ans * base;
        return ans;
    }
};
int main(){
     scanf("%d%d%d",&n,&m,&k); 
     Matrix adj(n,n);
     for(int i = 1; i <= m; i++){
            int u,v; scanf("%d%d",&u,&v);
            adj[u - 1][v - 1]++; 
     }
     cout<<adj.pow(k)[0][n - 1]<<endl;
}