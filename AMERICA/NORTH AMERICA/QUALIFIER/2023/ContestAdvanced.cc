#include "bits/stdc++.h"

using namespace std; 

const int maxf = 2e5 + 2; 
int t[maxf], s[maxf], cc[maxf]; 

int main(void){
    int n, k, c; 
    cin >> n >> k >> c;
    int ctr = 0;
    for(int i = 0; i < n; i++){
        cin >> t[i] >> s[i]; 
        if(ctr < k && cc[s[i]] < c)
        {
            cc[s[i]]++; 
            ctr += 1; 
        }
    }
    for(int i = 0; i < n; i++){
        if(cc[s[i]])
        {
            cout << t[i] << '\n'; 
            cc[s[i]]--; 
        }
        else if(ctr < k)
        {
            cout << t[i] << '\n'; 
            ctr++; 
        }
    }
    return 0; 
}