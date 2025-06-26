#include "bits/stdc++.h"
using namespace std;
int main(void)
{
    int N, X; 
    while(cin >> N >> X)
    {
        vector<int>arr(N); 
        for(int i = 0; i < N; i++) cin >> arr[i]; 
        vector<int>dyn(N, 1); 
        for(int i = N - 2; i >= 0; i--)
        {
            if(arr[i + 1] <= arr[i] + X) dyn[i] = dyn[i + 1] + 1; 
        }
        cout << *max_element(dyn.begin(), dyn.end()) << '\n'; 
    }
    return 0;
}