#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
#define int64_t long long
 
int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    vector<string>s(4);
    vector<int64_t>a(4);  
    for(int i = 0; i < 4; i++) { 
        cin >> s[i]; 
        a[i] = stoll(s[i]); 
    }     
    vector<__int128_t>num, den; 
    int na = sz(s[0]), nb = sz(s[1]); 
    for(int mask = 1; mask < (1 << na); mask++) {
        int flag = true; 
        __int128_t sum = 0; 
        for(int i = 0; i < na; i++) if(mask & (1 << i)) { 
            if(!sum) { 
                if(s[0][i] == '0') {
                    flag = false;  
                    break; 
                }
            }
            sum = 10 * sum + (s[0][i] - '0'); 
        }
        if(!flag) continue; 
        num.push_back(sum); 
    }
    for(int mask = 1; mask < (1 << nb); mask++) {
        int flag = true; 
        __int128_t sum = 0; 
        for(int i = 0; i < nb; i++) if(mask & (1 << i)) { 
            if(!sum) { 
                if(s[1][i] == '0') {
                    flag = false;  
                    break; 
                }
            }
            sum = 10 * sum + (s[1][i] - '0'); 
        }
        if(!flag) continue; 
        den.push_back(sum); 
    }
    sort(den.begin(), den.end());
    int64_t g = gcd(a[3], a[2]); 
    a[2] = a[2] / g;
    a[3] = a[3] / g;
    for(int i = 0; i < sz(num); i++) {
        int64_t x = num[i], y = a[2]; 
        __uint128_t prod = __uint128_t(x) * __uint128_t(a[3]); 
        if(prod % y == 0) { 
            __int128_t d = prod / y;
            auto it = lower_bound(den.begin(), den.end(), d);
            if(it != den.end() && *it == d && x <= __int128_t(a[0]) && d <= __int128_t(a[1])) { 
                cout << "possible\n" << (int64_t) x << " " << (int64_t) d << '\n'; 
                exit(0); 
            }
        }
    } 
    cout << "impossible\n"; 
    return 0;
}