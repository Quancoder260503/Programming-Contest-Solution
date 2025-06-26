#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

string S; 
int64_t A, B, X; 
const int maxf = 1e5 + 2; 

int64_t dyn[12][2][maxf], allow_digit[10];  

int64_t memo(const string &s, int pos, int is_equal, int mod) {
    if(pos == s.size()) return (mod == 0); 
    int64_t &ret = dyn[pos][is_equal][mod]; 
    if(ret != -1) return ret; 
    ret = 0; 
    int bound = is_equal ? s[pos] - '0' : 9; 
    for(int digit = (pos == 0); digit <= bound; digit++) if(allow_digit[digit]) { 
        ret += memo(s, pos + 1, (digit == bound) & is_equal, (10 * mod + digit) % X);  
    }
    return ret; 
}

int main(void) { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    cin >> X >> A >> B >> S; 
    for(int i = 0; i < S.size(); i++) { 
        allow_digit[S[i] - '0'] = true; 
    }
    if(X > maxf) {
        int ret = 0; 
        for(int cc = 1; 1LL * cc * X <= B; cc++) { 
            int64_t y = 1LL * cc * X; 
            if(y >= A) { 
                string c = to_string(y); 
                int check = true; 
                for(int p = 0; p < c.size(); p++) { 
                    check = check & allow_digit[c[p] - '0']; 
                }
                ret += check; 
            }
        } 
        cout << ret << '\n'; 
        return 0; 
    }
    int64_t ret = 0;
    string b = to_string(B), a = to_string(A - 1);
    for(int i = 0; i < b.size(); i++) { 
        memset(dyn, -1, sizeof(dyn)); 
        ret +=  memo(b.substr(i), 0, (i == 0), 0);
    }
    for(int i = 0; i < a.size(); i++) { 
        memset(dyn, -1, sizeof(dyn));  
        ret = ret - memo(a.substr(i), 0, (i == 0), 0);
    }
    cout << ret << '\n';  
    return 0; 
}