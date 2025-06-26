#include "bits/stdc++.h"

using namespace std;

int main(void) { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    string S; 
    cin >> S; 
    int N = S.size(); 
    S = " " + S; 
    vector<int>dyn(N + 1);
    for(int i = 1; i <= N; i++) { 
        for(int j = 1; j < i; j++) if(S[i] > S[j]) { 
            dyn[i] = max(dyn[i], dyn[j] + 1); 
        }
    } 
    int ret = *max_element(dyn.begin(), dyn.end()); 
    cout << 25 - ret << '\n'; 
    return 0; 
}