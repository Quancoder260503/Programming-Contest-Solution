#include "bits/stdc++.h"

using namespace std; 
const int maxf = 1e6 + 2; 

int arr[maxf]; 
int main(void)
{
    int n, q; 
    while(cin >> n >> q)
    {
        vector<int>prefix(n + 1), suffix(n + 1); 
        for(int i = 1; i <= n; i++) cin >> arr[i]; 
        for(int i = 1; i <= n; i++) prefix[i] = prefix[i - 1] + arr[i]; 
        for(int i = n - 1; i >= 0; i--) suffix[i] = suffix[i + 1] + arr[i + 1];  
        reverse(suffix.begin(), suffix.end()); 
        for(int i = 0; i < q; i++)
        {
            int x; 
            cin >> x;
            int flag = (x == 0);  
            for(int i = 0; i <= n; i++) 
            {
                auto pos = lower_bound(suffix.begin(), suffix.begin() + n - i, x - prefix[i]) - suffix.begin();
                if(pos < suffix.size() && suffix[pos] + prefix[i] == x)
                {
                    flag = 1; 
                    break; 
                } 
            }
            cout << (flag ? "Yes" : "No") << '\n'; 
        }
    }
    return 0; 
}