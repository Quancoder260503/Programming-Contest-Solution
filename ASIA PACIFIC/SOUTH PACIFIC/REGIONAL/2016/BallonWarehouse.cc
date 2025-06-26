#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 10; 

vector<pair<int, int>>g[maxf]; 
vector<int>ret;

int N, L, R;

void doit(int u, int pos) 
{
    if((int) ret.size() > maxf) return; 
    ret.push_back(u);
    for(auto v : g[u]) 
    {
        if(v.second < pos) break; 
        doit(v.first, v.second);
    } 
    return;    
}

int main(void)
{
    cin >> N >> L >> R; 
    for(int i = 0; i < N; i++)
    {
        int U, V; 
        cin >> U >> V; 
        g[U].push_back({V, i}); 
    }    
    for(int i = 0; i < maxf; i++) reverse(g[i].begin(), g[i].end()); 
    doit(0, 0);
    for(int i = L; i < R; i++) cout << ret[i % ret.size()] << " "; 
    cout << '\n'; 
    return 0;
}