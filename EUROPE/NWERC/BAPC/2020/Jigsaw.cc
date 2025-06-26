#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int C, E, M;
    while (cin >> C >> E >> M)
    {
        int64_t sum = C + E + M; 
        if(C != 4) 
        {
            cout << "impossible" << '\n'; 
            goto done; 
        }
        for(int i = 1; i * i <= sum; i++) if(sum % i == 0)
        {
            int64_t h = i, w = sum / i; 
            if(2 * (h + w - C) == E) 
            {
                cout << h << " " << w << '\n'; 
                goto done; 
            }
        }
        cout << "impossible";
    done:;  
    }
    return 0;
}