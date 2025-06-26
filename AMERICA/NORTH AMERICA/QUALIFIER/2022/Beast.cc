#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>arr(N); 
        for(int i = 0; i < N; i++)
        {
            cin >> arr[i]; 
        }
        sort(arr.rbegin(), arr.rend()); 
        int ret = 0; 
        int64_t sum, cur; 
        sum = cur = 0; 
        for(int i = 0; i < N; i++)
        {
            cur += arr[i];
            if(sum <= cur)
            {
                ret = i + 1; 
                sum += cur; 
                cur = 0; 
            }
        }
        cout << ret << '\n'; 
    }
    return 0;
}