#include "bits/stdc++.h"

using namespace std; 

int n, k; 
string S, s; 
vector<vector<int>>nxt, dyn;
vector<vector<vector<int>>>ndyn; 

int memo(int pos, int remain) { 
    if(remain < 0) return false; 
    int &ret = dyn[pos][remain]; 
    if(ret != -1) return ret;
    ret = false; 
    for(int i = 0; i < 26; i++) {
        if(nxt[pos][i] != -1 && memo(nxt[pos][i], remain - 1)) { 
            return ret = true; 
        }
    }
    return ret = (remain == 0); 
}

int memo2(int pos, int greater, int remain) {
    if(remain == k) return greater; 
    int &ret = ndyn[pos][remain][greater]; 
    if(ret != -1) return ret;
    ret = false; 
    for(int ch = (greater ? 0 : S[remain] - 'A'); ch < 26; ch++) { 
        if(nxt[pos][ch] != -1 && memo2(nxt[pos][ch], greater | (ch > (S[remain] - 'A')), remain + 1)) { 
            return ret = true; 
        }
    } 
    return ret; 
}

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0);
    cin >> n >> k;  
    vector<pair<string, int>>T; 
    vector<string>res(n); 
    for(int i = 0; i < n; i++) {
        cin >> s; 
        T.push_back({s, i}); 
    } 
    sort(T.begin(), T.end()); 
    s = T[0].first; 
    nxt.resize(s.size(), vector<int>(26, -1));
    dyn.resize(s.size(), vector<int>(k,  -1)); 
    for(int i = 0; i < s.size(); i++) { 
        for(int j = i - 1; j >= 0; j--) { 
            nxt[j][s[i] - 'A'] = i; 
            if(s[i] == s[j]) break; 
        }
    }
    S += s[0]; 
    for(int rem = k - 1, st = 0; rem >= 0; rem--) {
        for(int ch = 0; ch < 26; ch++) if(nxt[st][ch] != -1 && memo(nxt[st][ch], rem - 1)){ 
            S += char(ch + 'A'); 
            st = nxt[st][ch]; 
            break; 
        } 
    }
    res[T[0].second] = S; 
    for(int iter = 1; iter < T.size(); iter++) {
        s = T[iter].first; 
        nxt.clear(); 
        ndyn.clear(); 
        nxt.resize(s.size(), vector<int>(26, -1));
        ndyn.resize(s.size(), vector<vector<int>>(k, vector<int>(2, -1))); 
        for(int i = 0; i < s.size(); i++) { 
            for(int j = i - 1; j >= 0; j--) { 
                nxt[j][s[i] - 'A'] = i; 
                if(s[i] == s[j]) break; 
            }
        }
        int state = (S[0] < s[0]); 
        string nS; 
        nS += s[0];
        for(int rem = 1, st = 0; rem < k; rem++) {  
            for(int ch = (state ? 0 : S[rem] - 'A'); ch < 26; ch++) { 
                if(nxt[st][ch] != -1 && memo2(nxt[st][ch], state | ((S[rem] - 'A') < ch), rem + 1)) { 
                    state |= (S[rem] - 'A' < ch); 
                    nS += char(ch + 'A'); 
                    st = nxt[st][ch];
                    break;
                } 
            }
        }
        if(!state) { 
            cout << "NO\n";
            return 0;  
        }
        S.swap(nS); 
        if(s.size() >= k && S.size() < k) { 
           cout << "NO\n"; 
           return 0; 
        }
        res[T[iter].second] = S; 
    }
    cout << "YES\n"; 
    for(int i = 0; i < n; i++) { 
        cout << res[i] << '\n'; 
    }
    return 0; 
}