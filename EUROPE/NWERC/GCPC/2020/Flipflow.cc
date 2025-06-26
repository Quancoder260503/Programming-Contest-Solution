#include "bits/stdc++.h"
using namespace std;
int main(void)
{
    int N, S, T;
    while(cin >> T >> S >> N)
    {
        vector<int>a(N); 
        for(int i = 0; i < N; i++) cin >> a[i]; 
        a.push_back(T); 
        int ret = S; 
        N = a.size(); 
        for(int i = 1; i < N; i++)
        {
            ret = max(0, ret - (a[i] - a[i - 1])); 
            ret = S - ret; 
        }
        cout << S - ret << '\n'; 
    }
    return 0;
}