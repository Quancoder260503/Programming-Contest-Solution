#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    string s; 
    cin >> s;
    int n = s.size(); 
    vector<int>freq(7, 0); 
    int ret = 0; 
    for(int i = 0; i < n; i++) { 
        int mask = 1 << (s[i] - 'A'); 
        for(int j = 6; j >= 0; j--) { 
            if((mask & j) > 0 || (j > 0 && freq[j] == 0)) continue; 
            if(freq[j] == 0) { 
                freq[j]++;
                ret++; 
            }
            freq[j]--; 
            int to = j | mask; 
            if(to == 7) to = 0; 
            freq[to]++;
            break; 
        }
    }
    cout << ret << '\n'; 
    return 0; 
}