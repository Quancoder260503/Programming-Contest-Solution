#include "bits/stdc++.h"

using namespace std;
const int N = 2e5;

int64_t dist[N]; 

int main(void)
{
    int n, k; 
    string S;
    cin >> S >> k;
    n = S.length(); 
    queue<int>q; 
    memset(dist, -1, sizeof(dist)); 
    for(int i = 0; i < n; i++) if(S[i] == 'E')
    {
        q.push(i); 
        dist[i] = 0; 
    }
    while(q.size())
    {
        int u = q.front();
        q.pop(); 
        int tmp = u;  
        u--; 
        if(u < 0) u += n; 
        if(dist[u] == -1)
        {
            dist[u] = dist[tmp] + 1; 
            q.push(u); 
        }
    }
    int64_t ret = 0;  
    for(int i = 0; i < n; i++) if(dist[i] != -1) ret += max(0LL, 1LL * k - dist[i]); 
    cout << ret << '\n'; 
    return 0; 
}