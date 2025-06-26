#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int N; 
    while(cin >> N)
    {
        int ctr = 0; 
        vector<int>arr(N); 
        for(int i = 0; i < N; i++) cin >> arr[i]; 
        for(int i = 0; i < N; i++)
        {
            int j = i + 1; 
            while(j < N && arr[j] <= arr[j - 1]) j++; 
            i = j - 1;  
            ctr++; 
        }
        cout << ctr << '\n'; 
    }
    return 0;
}