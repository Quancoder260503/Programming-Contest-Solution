#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    int n, k; 
    cin >> k >> n; 
    vector<int>ctr(k + 1); 
    for(int i = 0, x; i < n; i++) { 
        cin >> x; 
        ctr[x]++; 
    }
    for(int i = 1; i <= k; i++) { 
        ctr[i]++; 
        int flag = 1; 
        for(int j = 2; j <= k; j++) flag &= (ctr[j] == ctr[1]);
        if(flag) { 
            cout << '+' << i << '\n';
            return 0;  
        }
        ctr[i]--; 
    }
    for (int i = 1; i <= k; i++)
    {
        ctr[i]--;
        int flag = 1;
        for (int j = 2; j <= k; j++) flag &= (ctr[j] == ctr[1]);
        if (flag) {
            cout << '-' << i << '\n';
            return 0;
        }
        ctr[i]++;
    }
    int mx = *max_element(ctr.begin() + 1, ctr.end()); 
    int mn = *min_element(ctr.begin() + 1, ctr.end());
    int rem = (n - mx - mn); 
    if(rem % (k - 2) == 0) { 
        int sz = rem / (k - 2); 
        int ptr = 0; 
        vector<int>ret;
        for(int i = 1; i <= k; i++) { 
            if(sz == ctr[i]) {
                ptr++; 
            }
            else {
                ret.push_back(i); 
            }
        }
        if(ptr == k - 2) { 
            if(ctr[ret[0]] > ctr[ret[1]]) swap(ret[0], ret[1]);
            if(ctr[ret[1]] - ctr[ret[0]] == 2) { 
                cout << '-' << ret[1] << " " << '+' << ret[0] << '\n';
                return 0;  
            }
        }
    } 
    cout << "*" << '\n'; 
    return 0; 
}