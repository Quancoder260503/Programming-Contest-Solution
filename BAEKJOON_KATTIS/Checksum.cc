#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int T; 
    cin >> T; 
    for(int tc = 0; tc < T; tc++)
    {
        int N;
        cin >> N; 
        vector<int>fa(2 * N); 
        iota(fa.begin(), fa.end(), 0); 
        vector<vector<int>>a(N, vector<int>(N)), b(N, vector<int>(N)); 
        for(int i = 0; i < N; i++) for(int j = 0; j < N; j++)
        {
            cin >> a[i][j]; 
        }
        int ret = 0;
        for(int i = 0; i < N; i++) for(int j = 0; j < N; j++)
        {
            cin >> b[i][j]; 
            ret += b[i][j]; 
        }
        vector<tuple<int, int, int>>edge; 
        for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) if(a[i][j] == -1)
        {
            edge.push_back({b[i][j], i, N + j}); 
        }
        sort(edge.rbegin(), edge.rend()); 
        function<int(int)>find = [&](int u) -> int
        {
            return u == fa[u] ? u : fa[u] = find(fa[u]); 
        }; 
        for(auto [W, U, V] : edge)
        {
            if(find(U) == find(V)) continue; 
            ret = ret - W; 
            fa[find(U)] = find(V); 
        }
        cout << "Case #" << tc + 1 << ": " << ret << '\n';
        for (int i = 0, x = 0; i < 2 * N; i++) cin >> x;
    } 
    return 0; 
}