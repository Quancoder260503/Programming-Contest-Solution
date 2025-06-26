#include "bits/stdc++.h"

using namespace std; 

int main(void){
    int n; 
    cin >> n;
    int res = -1;
    vector<string>cc;  
    for(int i = 0; i < n; i++)
    {
        string s; int l; 
        cin >> s >> l; 
        int ret = 0; 
        for(int j = 0; j < l; j++)
        {
            char a, b, c; 
            cin >> a >> b >> c; 
            if(a == 'Y' && b == 'Y' && c == 'Y') ret++; 
            else if(a == 'Y' && c == 'Y') ret++; 
            else if(a == 'N' && c == 'N') ret++; 
        } 
        if(ret > res) 
        {
            res = ret;
            cc.clear();
            cc.push_back(s); 
        }
        else if(ret == res) cc.push_back(s); 
    }
    sort(cc.begin(), cc.end()); 
    cout << cc[0] << '\n'; 
    return 0; 
}