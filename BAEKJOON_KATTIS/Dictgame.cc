#include "bits/stdc++.h"

using namespace std; 

const int maxf = 4e6 + 50; 

int trie[maxf][26], sg[maxf], up[maxf], nodes;

int upd(const char *s) { 
    int rt = 0; 
    int sz = strlen(s); 
    for(int i = 0; i < sz; i++) { 
        if(!trie[rt][s[i] - 'a']) trie[rt][s[i] - 'a'] = ++nodes; 
        up[trie[rt][s[i] - 'a']] = rt; 
        rt = trie[rt][s[i] - 'a']; 
    }
    return rt; 
}

void calc(int u) {
    sg[u] = 0;
    for (int i = 0; i < 26; i++) if (trie[u][i]) sg[u] = sg[u] ^ (1 + sg[trie[u][i]]);
    return;
}

void dfs(int u) {  
    for(int i = 0; i < 26; i++) if(trie[u][i]) dfs(trie[u][i]); 
    calc(u); 
    return;  
}

void jump(int c) { 
    while(c) { 
        calc(c); 
        c = up[c]; 
    }
    calc(0); 
    return; 
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int tc; 
    cin >> tc; 
    for(int _ = 0, n, q; _ < tc; _++) {
        cin >> n; 
        string s;
        nodes = 0;
        for(int i = 0; i < n; i++) { 
            cin >> s; 
            upd(s.c_str()); 
        }
        dfs(0); 
        cin >> q; 
        cout << "Case " << _ + 1 << ":\n";  
        for(int i = 0; i < q; i++) { 
            cin >> s;
            jump(upd(s.c_str())); 
            cout << (sg[0] ? 1 : 2) << '\n'; 
        }
        for(int i = 0; i <= nodes; i++) for(int j = 0; j < 26; j++) trie[i][j] = 0; 
    }
    return 0; 
}