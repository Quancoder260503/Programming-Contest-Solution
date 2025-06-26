#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int N, M; 
    while(cin >> N >> M)
    {
        vector<int>fa(N + 1); 
        iota(fa.begin(), fa.end(), 0); 
        function<int(int)>find = [&](int u) -> int 
        {
            return fa[u] == u ? u : fa[u] = find(fa[u]); 
        }; 
        for(int i = 0; i < M; i++)
        {
            int U, V; 
            cin >> U >> V; 
            if(V == N || U == N || find(U) == find(V)) continue; 
            fa[find(U)] = find(V); 
        }
        for(int i = 1; i <= N; i++) cout << (find(i) == find(N - 1) ? "A" : "B");
        cout << '\n';  
    }
    return 0; 
}