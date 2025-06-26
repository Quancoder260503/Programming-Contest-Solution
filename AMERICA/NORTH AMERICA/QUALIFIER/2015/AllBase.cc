#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

const int64_t inf = INT32_MAX; 

int64_t f(int base, string s){
    if(base == 1) { 
        int check = true; 
        for(int i = 0; i < s.size(); i++) check &= (s[i] == '1'); 
        if(check) { 
            return s.size(); 
        }
    }
    reverse(s.begin(), s.end()); 
    int64_t x = 1, ret = 0; 
    for(int i = 0; i < s.size(); i++) { 
        int c = ('0' <= s[i] && s[i] <= '9' ? s[i] - '0' : s[i] - 'a' + 10);
        if(ret > inf || 1LL * x * c > inf || c >= base) return INT32_MAX; 
        ret += x * c; 
        x = x * base;
    } 
    return ret;
}

int 
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0); 
    int tc; 
    for(cin >> tc; tc--; ) { 
        string s1, op, s2, eq, s3; 
        cin >> s1 >> op >> s2 >> eq >> s3; 
        if(op == "-") { op = "+"; swap(s1, s3); } 
        if(op == "/") { op = "*"; swap(s1, s3); }
        vector<int>ret; 
        if(op == "+") { 
            for(int i = 1; i <= 36; i++) { 
                int64_t a = f(i, s1), b = f(i, s2), c = f(i, s3); 
                if(a == inf || b == inf || c == inf) continue; 
                if(a + b == c) ret.push_back(i); 
            }
        }
        else { 
            for(int i = 1; i <= 36; i++) { 
                int64_t a = f(i, s1), b = f(i, s2), c = f(i, s3); 
                if(a == inf || b == inf || c == inf) continue; 
                if(1LL * a * b == c) ret.push_back(i); 
            }
        }
        if(ret.size() == 0) { 
            cout << "invalid\n"; 
        }
        else { 
            for(auto &x : ret) { 
               if(x <= 9) cout << x;
               else         cout << (x == 36 ? '0' : char(x - 10 + 'a'));  
            } 
            cout << '\n'; 
        }
    }  
    return 0; 
}