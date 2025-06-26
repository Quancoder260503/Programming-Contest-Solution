#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n; 
    string sa, sb;
    cin >> sa >> sb;
    int res = 0; 
    for(auto c : {'A', 'B', 'C', 'D', 'E'}) { 
        for(auto c2 : {'A', 'B', 'C', 'D', 'E'}) {
            string sc = sa;  
            int ret = 0; 
            for(int i = 0; i < sc.size(); i++) { 
               if(sc[i] == c) sc[i] = c2; 
               ret += (sc[i] == sb[i]); 
            } 
            res = max(ret, res);
        } 
    }
    cout << res << '\n'; 
    return 0; 
}