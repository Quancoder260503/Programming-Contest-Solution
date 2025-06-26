#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>arr(N); 
        for(int i = 0; i < N; i++)
        {
            cin >> arr[i];  
        }
        stack<int>stk; 
        vector<int>prefix(N + 1); 
        for(int i = 0; i < N; i++)
        {
            while(stk.size() && arr[stk.top()] < arr[i])
            {
                stk.pop(); 
            }
            int L = (stk.size() ? (i + stk.top()) / 2 : -1); 
            int R = i; 
            if(L < R)
            {
                prefix[L + 1]++; 
                prefix[R]--; 
            }
            stk.push(i); 
        }
        while(stk.size()) stk.pop(); 
        for(int i = N - 1; i >= 0; i--)
        {
            while(stk.size() && arr[stk.top()] < arr[i])
            {
                stk.pop(); 
            }
            int L = i; 
            int R = (stk.size() ? (i + stk.top() + 1) / 2 : N);
            if(L < R)
            {
                prefix[L + 1]++; 
                prefix[R]--; 
            }
            stk.push(i); 
        }
        for(int i = 0; i < N; i++)
        {
            prefix[i + 1] += prefix[i]; 
        }
        for(int i = 0; i < N; i++)
        {
            cout << prefix[i] << ' '; 
        }
    }
    return 0; 
}