#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int N;
    while (cin >> N)
    {
        vector<int>arr(N); 
        for (int i = 0; i < N; i++)
        {
            cin >> arr[i]; 
        }
        sort(arr.begin(), arr.end()); 
        int64_t ret = 0; 
        for(int i = 0; i < N; i++)
        {
            ret += arr[i]; 
            while(i < N && arr[i] + 1 == arr[i + 1]) i++; 
        }
        cout << ret << '\n'; 
    }
    return 0;
}