#include "bits/stdc++.h"

using namespace std;

int main(void)
{ 
    int N, D;
    cin >> N >> D; 
    int64_t ret = 0; 
    map<int, int>mp; 
    for(int i = 0; i < N; i++) 
    {
        int x; 
        cin >> x; 
        ret += mp[x / D]; 
        mp[x / D]++; 
    }
    cout << ret << '\n'; 
    return 0;
}