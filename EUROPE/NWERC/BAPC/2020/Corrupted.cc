#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int N, P; 
    while(cin >> N >> P)
    {
        vector<int>arr(N); 
        for(int i = 0; i < N; i++) cin >> arr[i]; 
        if(*max_element(arr.begin(), arr.end()) == 0)
        {
            for(int i = 0; i < N; i++) cout << 0 << '\n';
            continue; 
        }
        vector<int>ctr(N); 
        ctr[N - 1] = (arr[N - 1] > 0); 
        for(int i = N - 2; i >= 0; i--)
        {
            ctr[i] = ctr[i + 1] + (arr[i] > arr[i + 1]); 
        }
        if(ctr[0] != P) cout << "ambiguous" << '\n'; 
        else 
        {
            for(int i = 0; i < N; i++) cout << ctr[i] << '\n'; 
        }
    }
    return 0;
}