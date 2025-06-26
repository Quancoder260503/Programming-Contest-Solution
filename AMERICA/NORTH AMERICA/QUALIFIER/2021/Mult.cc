#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>arr(N); 
        for(int i = 0; i < N; i++) cin >> arr[i]; 
        int start; 
        int flag = 0;  
        for(int i = 0; i < N; i++)
        {
            if(!flag)
            {
                start = arr[i]; 
                flag = 1; 
            }
            else if(arr[i] % start == 0) 
            {
                cout << arr[i] << '\n'; 
                flag = 0; 
            }
        }
    }
    return 0; 
}