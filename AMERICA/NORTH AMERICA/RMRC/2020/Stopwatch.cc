#include "bits/stdc++.h"
using namespace std; 
int main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int> T(N);
        int ret = 0;
        for (int i = 0; i < N; i++) cin >> T[i];
        if(N & 1)
        {
            puts("still running"); 
            continue; 
        }
        for(int i = 1; i < N; i++)
        {
            if(i & 1) ret += (T[i] - T[i - 1]); 
        } 
        cout << ret << '\n'; 
    }
    return 0; 
}