#include "bits/stdc++.h"

using namespace std;

struct fenwick
{
    int N;
    vector<int> bit;
    void init(int _N)
    {
        N = _N;
        bit.resize(N);
    }
    int sum(int i)
    {
        int c = 0;
        for (++i; i > 0; i -= (i & -i))
        {
            c = c + bit[i];
        }
        return c;
    }
    void upd(int i, int dif)
    {
        for (++i; i < N; i += (i & -i))
        {
            bit[i] = dif + bit[i];
        }
    }
};

const int maxf = 1e5; 

int vis[maxf + 10], ret[maxf + 10]; 
vector<int>prime[maxf + 10];  
vector<pair<int, int>>query[maxf + 10]; 

void init(void)
{
    for(int i = 2; i <= maxf; i++) 
    {
        if(vis[i]) continue; 
        prime[i].push_back(i); 
        for (int j = 2 * i; j <= maxf; j += i)
        {
            prime[i].push_back(j); 
            vis[j] = 1; 
        }
    }
    return; 
}

int main(void)
{
    int Q; 
    init(); 
    while(cin >> Q)
    {
        for(int i = 0; i < Q; i++)
        {
            int U, V; 
            cin >> U >> V;
            query[V].push_back({U, i});        
        }
        fenwick fenw; 
        fenw.init(maxf + 2); 
        for(int i = 2; i <= maxf; i++)
        {
            fenw.upd(i, 1); 
        }
        for(int i = maxf; i > 1; i--)
        {
            for(int j = 0; j < query[i].size(); j++)
            {
                int idx = query[i][j].second; 
                int at  = query[i][j].first;
                ret[idx] = fenw.sum(at); 
            }
            for(auto m : prime[i])
            {
                if(fenw.sum(m) > fenw.sum(m - 1)) fenw.upd(m, -1); 
            }
        }
        for(int i = 0; i < Q; i++) cout << ret[i] << '\n'; 
    }
    return 0; 
}