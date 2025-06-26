#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N, S; 
    while(cin >> N >> S)
    {
        vector<int>arr(N); 
        for(int i = 0; i < N; i++) cin >> arr[i];
        int ret = *max_element(arr.begin(), arr.end()); 
        ret = ceil(ret * S / 1000.0); 
        cout << ret << '\n'; 
    }
    return 0; 
}