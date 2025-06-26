#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int T;
    cin >> T;  
    while(T--)
    {
        int64_t N, M, X, Y; 
        cin >> N >> M >> X >> Y; 
        X--, Y--; 
        for(int i = 0; i < N; i++)
        {
            int64_t ret = i * M + Y; 
            if(ret % N == X)
            {
                cout << ret + 1 << '\n';
                goto done; 
            }
        }
        cout << -1 << '\n'; 
    done:; 
    }
    return 0;
}