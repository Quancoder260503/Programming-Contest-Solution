#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int cap, n;
    cin >> cap >> n;
    vector<int> arr(n);
    vector<int> acc(n);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        sum += arr[i];
    }
    if (sum <= cap)
    {
        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << '\n';
        }
        return 0;
    }
    while (true)
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i] == 0) continue;
            arr[i]--;
            acc[i]++;
            cap--;
            if (cap == 0) goto finish; 
        }
    }
finish: 
    for (int i = 0; i < n; i++)
    {
        cout << acc[i] << '\n';
    }
    return 0;
}