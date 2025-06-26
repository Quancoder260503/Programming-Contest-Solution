#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int tc;
    cin >> tc;
    while(tc--)
    {
        int n;
        string s;
        cin >> n >> s;  
        vector<int>ctr(128, 0); 
        vector<int>vis(128, 0); 
        for(int i = 0; i < n; i++) ctr[s[i]]++;
        int nused = 0;
        int64_t ret = 0; 
        for(int i = n - 1; i >= 0; i--)
        {
            if(!vis[s[i]])
            {
                ret += 1LL * (nused - (n - i - 1)) * ctr[s[i]]; 
                nused += ctr[s[i]]; 
                vis[s[i]] = 1; 
            }
        }
        cout << ret * 5 << '\n'; 
    }
    return 0; 
}