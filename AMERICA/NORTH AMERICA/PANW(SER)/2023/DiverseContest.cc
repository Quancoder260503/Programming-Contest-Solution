#include "bits/stdc++.h"

using namespace std;

struct problem { 
    vector<int>topic;
}; 

int main(void) {
    int n, k;
    cin >> n >> k;
    map<string, int>idx; 
    int type = 0; 
    vector<problem>pset; 
    for(int i = 0, x; i < n; i++) {  
        cin >> x; 
        problem curr; 
        for(int j = 0; j < x; j++) { 
            string s; 
            cin >> s; 
            if(idx.count(s) == 0) idx[s] = type++; 
            curr.topic.push_back(idx[s]); 
        }
        pset.push_back(curr); 
    }
    int ret = 0; 
    for(int mask = 0; mask < (1 << n); mask++) {
        int c = __builtin_popcount(mask);
        if(c != k) continue; 
        int flag = true;
        vector<int> freq(type, 0);
        for(int i = 0; i < n; i++) if(mask & (1 << i)) { 
            for(auto p : pset[i].topic) freq[p]++; 
        }
        for(int i = 0; i < type; i++) flag &= (freq[i] <= c / 2); 
        ret += flag; 
    }
    cout << ret << '\n'; 
    return 0;
}