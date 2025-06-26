#include "bits/stdc++.h"
using namespace std; 
const int L = 1000; 
int main(void)
{
    int N; 
    while(cin >> N)
    {
        for(int i = 0; i < N; i++)
        {
            int x;
            cin >> x; 
            for(int j = 0; j < L; j++) if((j xor (j << 1)) == x || (j xor (j << 1)) == x + 256)
            {
                cout << j << ' '; 
                break;
            } 
        }
    }
    return 0; 
}