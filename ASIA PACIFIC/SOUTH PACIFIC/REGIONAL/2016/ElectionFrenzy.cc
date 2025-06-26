#include "bits/stdc++.h"

using namespace std;
const int maxf = 1e6 + 2; 

int col[maxf]; 
vector<int>g[maxf]; 
set<int>adj[maxf]; 


int main(void)
{
    int N;
    cin >> N;
    if(N == 1)
    {
        cout << "Impossible" << '\n';
        return 0; 
    }
    int ret = 0;
    for(int i = 1; i <= N; i++)
    {
        char type; 
        int sz; 
        cin >> type >> sz; 
        if(type == 'C')
        {
            ret = ret | (sz == 0); 
            for (int j = 0; j < sz; j++)
            {
                int x;
                cin >> x;
                g[i].push_back(x);
            }
        }
        else 
        {
            ret = ret | (sz == N - 1); 
            for(int j = 0; j < sz; j++)
            {
                int x; 
                cin >> x; 
                adj[i].insert(x); 
            }
        }
    }
    if (ret)
    {
        cout << "Impossible" << '\n';
        return 0;
    }
    set<int>vis; 
    for(int i = 1; i <= N; i++) vis.insert(i); 
    auto bfs = [&](int src, int c)
    {
        col[src] = c; 
        vis.erase(src); 
        queue<int>q;
        q.push(src);  
        while(q.size())
        {
            int u = q.front();
            q.pop(); 
            if(g[u].size())
            {
                for(auto v : g[u])
                {
                    if(!col[v])
                    {
                        col[v] = col[u] xor 3; 
                        vis.erase(v); 
                        q.push(v); 
                    }
                }
            }
            else
            {
                vector<int>curr;
                for(auto v : vis) if(!adj[u].count(v)) 
                {
                    curr.push_back(v); 
                    q.push(v); 
                    col[v] = col[u] xor 3; 
                } 
                for(auto v : curr) vis.erase(v); 
            }
        }
        return; 
    };
    for(int i = 1; i <= N; i++)
    {
        if(!col[i]) bfs(i, 1); 
    }
    for(int i = 1; i <= N; i++)
    {
        cout << (col[i] == 1 ? 'S' : 'V'); 
    }
    cout << '\n'; 
    return 0;
}