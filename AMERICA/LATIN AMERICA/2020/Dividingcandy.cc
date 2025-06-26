#include "bits/stdc++.h"
using namespace std; 
const int M = 2e5 + 10; 
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>bit(M); 
        for(int i = 0; i < N; i++)
        {
            int at;
            cin >> at; 
            while(bit[at])
            {
                bit[at++] = 0; 
            }
            bit[at] = 1; 
        }
        int ret = 0; 
        for(int i = 0; i < M; i++)
        {
            ret += bit[i]; 
        }
        if(ret == 2 || ret == 1 && N > 1)
        {
            puts("Y"); 
        }
        else 
        {
            puts("N"); 
        }
    }
    return 0; 
}