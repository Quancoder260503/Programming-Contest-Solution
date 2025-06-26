#include "bits/stdc++.h"
using namespace std; 
int main(void)
{
    int H, K, V, S; 
    while(cin >> H >> K >> V >> S)
    {
        int ctr = 0; 
        while(H > 0)
        {
            V += S; 
            V = V - max(1, V / 10); 
            if(V >= K) H++; 
            if (0 < V && V < K)
            {
                H--;
                if(H == 0) V = 0; 
            }
            if(V <= 0) H = V = 0; 
            ctr += V; 
            if(S > 0) S--; 
        }   
        cout << ctr << '\n'; 
    }
    return 0; 
} 