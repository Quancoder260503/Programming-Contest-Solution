#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    string s; 
    cin >> s; 
    vector<int>ctr(26); 
    for(int i = 0; i < s.size(); i++) { 
        ctr[s[i] - 'A']++; 
    }
    auto chk = [&](int c) { 
        int mode = 0, sum = 0; 
        for(int i = 0; i < ctr.size(); i++) { 
            if(ctr[mode] < ctr[i]) mode = i; 
            sum += ctr[i]; 
        }
        return (ctr[mode] <= (sum + 1) / 2 && ctr[c] <= sum / 2); 
    }; 
    string ret; 
    int last = -1; 
    for(int i = 0; i < s.size(); i++) { 
        int flag = false;
        for(int j = 0; j < 26; j++) {
            if(ctr[j] == 0) continue;  
            if(last == -1 || last != j) {
                ctr[j]--;
                if(chk(j)) { 
                    ret += 'A' + j; 
                    last = j; 
                    flag = true; 
                    break; 
                }
                else ctr[j]++; 
            } 
        }
        if(!flag) { 
            cout << "-1\n"; 
            return 0; 
        }
    }
    cout << ret << '\n'; 
    return 0; 
}