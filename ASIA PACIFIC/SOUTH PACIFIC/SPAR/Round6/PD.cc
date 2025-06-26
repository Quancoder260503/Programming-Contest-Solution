#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<string>s(n);
    for(int i = 0; i < n; i++) cin >> s[i]; 
    string ret; 
    for(int i = 0; i < m; i++)
    {
        vector<int>ctr(26);
        for(int j = 0; j < n; j++) ctr[s[j][i] - 'a']++;
        int mx = -1; 
        for(int j = 0; j < 26; j++) mx = max(mx, ctr[j]);
        for(int j = 0; j < 26; j++) if(ctr[j] == mx)
        {
            ret += 'a' + j; 
            break; 
        }
    }
    cout << ret << '\n';
    return 0; 
}