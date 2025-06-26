#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int) 3e5 + 10;
int k, n;
int arr[MAXN]; 
signed main(void)
{
    cin >> k >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> arr[i]; 
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        int j = i; 
        while(j < n && arr[j] <= arr[j + 1])
        {
            j++; 
        }
        ans++; 
        i = j; 
    }
    ans--;
    cout << ans << '\n'; 
    return 0; 
}