#include "bits/stdc++.h"

using namespace std;
 
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int tc; 
    cin >> tc; 
    for(int _ = 0; _ < tc; _++)
    {
        int N; 
        cin >> N; 
        vector<int>ret(2); 
        map<vector<int>, int>mp; 
        int nodes = 0; 
        for(int turn = 0; turn < 2; turn++)
        {       
            vector<vector<int>>g(N);  
            for(int i = 0; i < N - 1; i++)
            {
                int U, V;
                cin >> U >> V;
                U--, V--;
                g[U].push_back(V);
                g[V].push_back(U); 
            }
            function<int(int, int)>doit = [&](int u, int p) -> int
            {
                vector<int>res;
                for(auto v : g[u]) if(v != p)
                {
                    res.push_back(doit(v, u));
                }
                sort(res.begin(), res.end()); 
                if(mp.count(res) == 0) mp[res] = nodes++; 
                return mp[res]; 
            };
            ret[turn] = doit(0, -1); 
        }
        cout << (ret[0] == ret[1] ? "YES" : "NO") << '\n';  
    }
    return 0;  
}