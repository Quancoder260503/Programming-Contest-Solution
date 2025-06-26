#include "bits/stdc++.h"
using namespace std; 
int main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int64_t>s(N); 
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                int64_t  x; 
                cin >> x; 
                s[i] += x;
            }
        }
        sort(s.begin(), s.end()); 
        int64_t ret = 0, sum = 0; 
        for(int i = 0; i < N / 2; i++) ret += s[i]; 
        for(int i = 0; i < N; i++) sum += s[i]; 
        ret = sum / 2 - ret; 
        cout << ret << '\n'; 
    }
    return 0; 
}