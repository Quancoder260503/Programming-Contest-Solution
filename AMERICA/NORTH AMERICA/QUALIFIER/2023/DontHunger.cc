#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);  
    int n, k; 
    cin >> n >> k;
    vector<int>a(n), b(n); 
    for(int i = 0; i < n; i++) { 
        cin >> a[i] >> b[i]; 
    } 
    double opt = 0, x = 1e9; 
    for(int i = 0; i < 100; i++, x = x / 2) { 
        double c = opt + x; 
        map<int, double>stk; 
        for(int i = 0; i < n; i++) { 
            stk[b[i]] += a[i]; 
            double rem = c; 
            while(stk.size()) { 
                if(stk.begin()->first <= i) { 
                   stk.erase(stk.begin()); 
                }
                else if(rem >= stk.begin()->second) { 
                   rem = rem - stk.begin()->second; 
                   stk.erase(stk.begin()); 
                }
                else if(stk.begin()->second >= rem) { 
                   stk.begin()->second -= rem; 
                   rem = 0; 
                   break; 
                }
            }
            if(rem > 0) { 
                c = opt; 
            }
        }
        opt = c; 
    }
    cout << fixed << setprecision(10); 
    if(opt > 0) cout << opt / k << '\n'; 
    else puts("-1"); 
    return 0; 
}