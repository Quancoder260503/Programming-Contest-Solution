#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int N, M; 
    int64_t L; 
    cin >> N >> M >> L; 
    multiset<pair<int64_t, int64_t>>point; 
    point.insert({0, 1}); 
    for(int i = 0; i < N; i++)
    {
        int64_t f; 
        cin >> f; 
        int64_t at = L + (i & 1 ? f : -f); 
        point.insert({at, i & 1 ? 2 : -2}); 
        L = 2 * at - L; 
    }
    point.insert({L, (N & 1 ? 1 : -1)}); 
    for(int i = 0; i < M; i++)
    {
        int64_t c; 
        cin >> c; 
        point.insert({c, 0}); 
    }
    point.insert({1LL << 62, 0}); 
    int64_t pre = -(1LL << 62); 
    int64_t sum = 0, acc = 0; 
    for(auto p : point)
    {
        sum += 1LL * (p.first - pre) * acc;
        acc += p.second; 
        pre = p.first;
        if(!p.second)
        {
            cout << sum << ' ';
            sum = 0;
        } 
    }
    cout << '\n'; 
    return 0;
}