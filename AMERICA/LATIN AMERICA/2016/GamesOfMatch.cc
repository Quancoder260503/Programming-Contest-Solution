#include "bits/stdc++.h"

using namespace std;  

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    string S; 
    cin >> S;
    int n = S.size(); 
    vector<int>text(n); 
    vector<int>last(26, -1); 
    for(int i = 0; i < n; i++) { 
        int c = S[i] - 'a'; 
        if(last[c] == -1) text[i] = -1; 
        else              text[i] = i - last[c]; 
        last[c] = i; 
    } 
    int m; 
    cin >> m; 
    vector<int>pattern(m); 
    fill(last.begin(), last.end(), -1); 
    for(int i = 0, c; i < m; i++) {
        cin >> c; 
        --c; 
        if(last[c] == -1) pattern[i] = -1; 
        else              pattern[i] = i - last[c]; 
        last[c] = i; 
    }
    vector<int>failure(m + 1, 1);  
    failure[0] = -1; 
    for(int i = 0, j = -1; i < m; ) { 
        while(j >= 0 && (pattern[i] > j ? -1 : pattern[i]) != pattern[j]) { 
            j = failure[j]; 
        }
        failure[++i] = ++j; 
    }
    int ret = 0; 
    for(int i = 0, j = 0; i < n; ) { 
        while(j < m && (text[i] > j  ? -1 : text[i]) != pattern[j]) { 
            j = failure[j]; 
        }
        j++; i++; 
        ret += (j == m);
        if(j == m) { j = failure[j]; } 
    }
    cout << ret << '\n'; 
    return 0; 
}