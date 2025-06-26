#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int n;
    while (cin >> n)
    {
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        stack<int> stk;
        int ret = n - 1;
        for (int i = 0; i < n; i++)
        {
            while (stk.size() && arr[stk.top()] < arr[i])
            {
                stk.pop(); 
            }
            ret += (stk.size() > 0); 
            if(stk.size() && stk.top() == i - 1) ret--; 
            stk.push(i); 
        }
        while(stk.size()) stk.pop(); 
        for(int i = n - 1; i >= 0; i--)
        {
            while (stk.size() && arr[stk.top()] < arr[i])
            {
                stk.pop();
            }
            ret += (stk.size() > 0);
            if (stk.size() && stk.top() == i + 1) ret--;
            stk.push(i);
        }
        cout << ret << '\n'; 
    }
    return 0;
}