#include "bits/stdc++.h"

using namespace std;

const int maxf = 2e5 + 10; 

#define sz(x) int(x.size())

vector<int>g[maxf]; 
int rem[maxf], deg[maxf];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0);
    int N, M, A, B; 
    cin >> N >> M >> A >> B;
    for(int i = 0, U, V; i < M; i++) { 
        cin >> U >> V; 
        --U, --V; 
        g[U].push_back(V); 
        g[V].push_back(U); 
    }
    set<pair<int, int>>ms; 
    for(int i = 0; i < N; i++) {
        deg[i] = sz(g[i]); 
        ms.insert({deg[i], i}); 
    }
    int ret = N; 
    for(;;) {
        int u; 
        if(sz(ms) && ms.begin()->first < A) { 
            u = ms.begin()->second; 
            ms.erase({deg[u], u}); 
        } 
        else if (sz(ms) && ret - 1 - ms.rbegin()->first < B) { 
            u = ms.rbegin()->second; 
            ms.erase({deg[u], u}); 
        }
        else break; 
        rem[u] = true;
        for(auto v : g[u]) if(!rem[v]) { 
            ms.erase({deg[v], v}); 
            deg[v]--; 
            ms.insert({deg[v], v}); 
        }
        ret--;
    }
    cout << ret << '\n'; 
    return 0;
}