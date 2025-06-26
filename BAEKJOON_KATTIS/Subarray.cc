#include "bits/stdc++.h"
using namespace std; 
int main(void)
{
    int N, K; 
    cin >> N >> K; 
    map<int64_t, int64_t>mp; 
    mp[0] = 1; 
    int64_t acc = 0; 
    int64_t ret = 0; 
    for(int i = 0; i < N; i++)
    {
        int x; 
        cin >> x; 
        acc += x; 
        ret += mp[acc - K]; 
        mp[acc]++; 
    }
    cout << ret << '\n'; 
    return 0; 
}