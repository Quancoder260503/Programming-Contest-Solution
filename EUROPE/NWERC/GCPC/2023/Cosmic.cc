#include "bits/stdc++.h"

using namespace std;

const int maxf = 3e5 + 2; 
const int64_t INF = 1e12; 

vector<int>g[maxf]; 
int W[maxf]; 

void calc_dist(vector<int>&dist, int src)
{
    fill(dist.begin(), dist.end(), -1); 
    dist[src] = 0; 
    queue<int>q; 
    q.push(src); 
    while(q.size())
    {
        int u = q.front();
        q.pop(); 
        for(auto v : g[u])
        {
            if(dist[v] == -1)
            {
                dist[v] = dist[u] + 1; 
                q.push(v); 
            }
        }
    }
    return; 
}

int main(void)
{
    int N, M, K; 
    cin >> N >> M >> K;
    for(int i = 0; i < K; i++)
    {
        int worm; 
        cin >> worm; 
        W[worm] = 1; 
    } 
    for(int i = 0; i < M; i++)
    {
        int U, V; 
        cin >> U >> V;
        g[U].push_back(V);
        g[V].push_back(U); 
    }
    vector<int>da(N + 1), db(N + 1); 
    calc_dist(da, 1);
    calc_dist(db, N); 
    pair<int64_t, int64_t> ret = {da[N], 1}; 
    int64_t sum = 0; 
    for(int i = 1; i <= N; i++) if(W[i])
    {
        sum += db[i]; 
    }
    for(int i = 1; i <= N; i++) if(W[i])
    {
        int64_t num = 1LL * (K - 1) * da[i] + sum - db[i]; 
        int64_t den = K - 1; 
        //cout << num << " " << den << " " << i << '\n'; 
        if(1LL * ret.second * num < 1LL * ret.first * den)
        {
            int g = gcd(num, den); 
            num /= g;
            den /= g; 
            ret = make_pair(num, den); 
        }

    }
    cout << ret.first << "/" << ret.second << '\n'; 
    return 0; 
}