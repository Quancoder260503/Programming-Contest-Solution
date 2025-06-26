#include "bits/stdc++.h"

using namespace std;

#define int64_t long long 

int main(void)
{
    int n; 
    cin >> n; 
    vector<pair<int, int>>arr; 
    int64_t ret = 0; 
    for(int i = 0, a, b; i < n; i++)
    {
        cin >> a >> b; 
        if(a > b) swap(a, b); 
        arr.push_back({a, b});
        ret = max(ret, 1LL * a * b);  
    }
    int bmx = 0; 
    sort(arr.rbegin(), arr.rend()); 
    for(int i = 0; i < n; i++)
    {
        ret = max(ret, 2LL * min(bmx, arr[i].second) * arr[i].first); 
        bmx = max(bmx, arr[i].second); 
    }
    cout << ret / 2 << "." << 5 * (ret & 1) <<'\n'; 
    return 0;
}