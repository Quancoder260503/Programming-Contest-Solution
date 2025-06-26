#include "bits/stdc++.h"

using namespace std;

string doit(int n, int &x)
{
    if(n == 1)
    {
        return "1";  
    }
    if(n & 1)
    {
        x += 2; 
        return doit((n - 1) / 2, x) + "d+1+"; 
    }
    else 
    {
        x += 1; 
        return doit(n / 2, x) + "d+"; 
    }
}

int main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>arr(N); 
        for(int i = 0; i < N; i++) cin >> arr[i]; 
        string ret;
        for(int i = N - 1; i >= 0; i--)
        {
            int x = 0;
            ret = doit(arr[i], x) + ret; 
            for(int j = 0; j < i; j++) arr[j] += x; 
        }
        cout << ret << '\n'; 
        /* 
        vector<int>chk; 
        for(int i = 0; i < ret.size(); i++)
        {
            if(ret[i] == '1') chk.push_back(1); 
            else if(ret[i] == 'd') chk.push_back(chk.back()); 
            else if(ret[i] == '+') 
            {
                int curr = chk.back(); 
                chk.pop_back();
                curr += chk.back(); 
                chk.pop_back(); 
                for(int j = 0; j < chk.size(); j++) chk[j]--; 
                chk.push_back(curr); 
            }
        }
        for(auto it : chk) cout << it << " "; 
        cout << '\n'; 
        */ 
    }
    return 0; 
}