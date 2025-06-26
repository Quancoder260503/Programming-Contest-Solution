#include "bits/stdc++.h"
using namespace std; 
int main(void)
{
    int N, M; 
    while(cin >> N >> M)
    {
        priority_queue<int, vector<int>, greater<int>>pq; 
        vector<pair<int, int>>T;
        for(int i = 0; i < N; i++)
        {
            int L, R;
            cin >> L >> R; 
            R += L; 
            T.push_back({L, R}); 
        }
        sort(T.begin(), T.end()); 
        int ret = 0; 
        for(int i = 0; i < N; i++)
        {
            while(pq.size() && pq.top() + M < T[i].first) pq.pop(); 
            if(pq.size() && pq.top() > T[i].first) 
            {
                pq.push(T[i].second); 
                continue; 
            }
            if(pq.size() && T[i].first - pq.top() <= M) 
            {
                pq.pop(); 
                pq.push(T[i].second); 
                ret++; 
                continue; 
            }
            else 
            {
                pq.push(T[i].second); 
            }
        }
        cout << ret << '\n'; 
    }
    return 0; 
}