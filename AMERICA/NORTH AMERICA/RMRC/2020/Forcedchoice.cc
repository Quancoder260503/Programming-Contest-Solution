#include "bits/stdc++.h"
using namespace std;
int main(void)
{
    int N, P, S, M; 
    while(cin >> N >> P >> S)
    {
        for(int i = 0; i < S; i++)
        {
            int ret = 0; 
            cin >> M;
            for(int j = 0; j < M; j++) 
            {
                int x;
                cin >> x;
                ret = ret | (x == P); 
            }
            cout << (ret ? "KEEP" : "REMOVE") << '\n'; 
        }
    }
    return 0; 
}