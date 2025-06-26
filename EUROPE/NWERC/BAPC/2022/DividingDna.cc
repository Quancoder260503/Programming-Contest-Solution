#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int N; 
    cin >> N;
    int pre = 0, ret = 0;  
    for(int i = 0; i < N; i++)
    {
        cout << "? " << pre << " " << i + 1 << '\n'; 
        string s; 
        cin >> s; 
        if(s == "absent")
        {
            pre = i + 1; 
            ret++; 
        }
    }
    cout << "! " << ret << '\n'; 
    return 0; 
}