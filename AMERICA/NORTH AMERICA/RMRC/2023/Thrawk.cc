#include "bits/stdc++.h"

using namespace std; 

#define sz(x) (int) x.size()

int main(void){ 
    int n;
    string s; 
    cin >> n >> s; 
    map<string, int>g; 
    function<int(string)>grundy = [&](string S)
    {
        if(sz(S) <= 1) return 0;
        if (g.count(S)) return g[S];
        int ctr = count(S.begin(), S.end(), 'B'); 
        if(ctr == 0 || ctr == sz(S)) return g[S] = 0;
        set<int>gr; 
        for(int i = 0; i + 1 < sz(S); i++) if(S[i] != S[i + 1]) {
            string l = S.substr(0, i) + S[i + 1]; 
            string r = S.substr(i + 2);
            gr.insert(grundy(l) ^ grundy(r));
            l = S.substr(0, i); 
            r = S[i] + S.substr(i + 2); 
            gr.insert(grundy(l) ^ grundy(r));  
        }
        int mex = 0; 
        while(gr.count(mex)) mex++;
        return g[S] = mex; 
    }; 
    vector<pair<int, string>>chunks; 
    for(int i = 0, j = 0; i < n; i++){ 
        if(s[i] == '.') continue; 
        for(j = i; j < n; j++) if(s[j] == '.') break; 
        chunks.push_back({i, s.substr(i, j - i)}); 
        i = j - 1; 
    }
    int nimsum = 0; 
    for(auto [c, v] : chunks) {
        nimsum = nimsum ^ grundy(v); 
    }
    if(nimsum == 0)
    {
        cout << 0 << '\n'; 
        return 0; 
    }
    vector<pair<int, int>>ret; 
    for(auto [c, v] : chunks) { 
        int nimtemp = nimsum ^ grundy(v); 
        for(int i = 0; i + 1 < sz(v); i++) if(v[i] != v[i + 1]) {
            string l = v.substr(0, i) + v[i + 1];
            string r = v.substr(i + 2);
            if((nimtemp ^ grundy(l) ^ grundy(r)) == 0) {
                ret.push_back({c + i + 1, c + i}); 
            }
            l = v.substr(0, i);
            r = v[i] + v.substr(i + 2);
            if((nimtemp ^ grundy(l) ^ grundy(r)) == 0) {
                ret.push_back({c + i, c + i + 1}); 
            }
        }
    }
    cout << sz(ret) << '\n';
    sort(ret.begin(), ret.end()); 
    for(auto [a, d] : ret) cout << a + 1 << " " << d + 1 << '\n'; 
    return 0; 
}