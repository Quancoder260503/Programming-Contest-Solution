#include "bits/stdc++.h"
using namespace std;
int L, K;
signed main(void)
{
    cin >> L >> K;
    vector<int> arr;
    for (int i = 0; i < K; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }
    sort(arr.begin(), arr.end());
    int acc = 0;
    int at; 
    for (at = 0; at < arr.size(); at++)
    {
        acc += arr[at];
        if (acc > L) break;
    }
    cout << at << endl;
    return 0;
}