#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int n;
    while (cin >> n)
    {
        vector<int> arr(n);
        int sum = 0; 
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
            sum += arr[i]; 
        }
        for(int i = 0; i < n; i++)
        {
            if(2 * arr[i] == sum)
            {
                cout << arr[i] << '\n'; 
                return 0; 
            }
        }
        cout << "BAD" << '\n'; 
    }
    return 0;
}