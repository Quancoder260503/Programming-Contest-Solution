#include "bits/stdc++.h"

using namespace std; 

#define sz(s) int(s.size())

const int inf  = 1e6;  
const int N = 80; 


int trie[N * N][27];
int dyn[N][N][N * N][2][2]; 
int idx; 

void add(const string &s, int root) {
    for(int i = 0; i < sz(s); i++) { 
        if(trie[root][s[i] - 'A' + 1] == -1) { 
            trie[root][s[i] - 'A' + 1] = idx++; 
        }
        root = trie[root][s[i] - 'A' + 1]; 
    } 
    if(trie[root][0] == -1) trie[root][0] = idx++; 
    //cout << s << " " << root << " " << trie[root][0] << '\n'; 
    return;
}

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    int n, m, k; 
    memset(trie, -1, sizeof(trie)); 
    cin >> n >> m >> k;
    vector<vector<char>>g(n, vector<char>(m));  
    for(int i = 0; i < n; i++) 
    for(int j = 0; j < m; j++) { 
        cin >> g[i][j]; 
    }
    idx = 1;
    int root = 0;  
    for(int i = 0; i < k; i++) { 
        string s; cin >> s; 
        add(s, root); 
    }
    memset(dyn, -1, sizeof(dyn)); 
    function<int(int, int, int, int, int)> func = [&](int i, int j, int k, int go_left, int go_right) -> int { 
        if(dyn[i][j][k][go_left][go_right] != -1) return dyn[i][j][k][go_left][go_right]; 
        int &ret = dyn[i][j][k][go_left][go_right]; 
        ret = inf;
        if(i + 1 < n && trie[k][g[i + 1][j] - 'A' + 1] != -1) { 
            ret = min(ret, 1 + func(i + 1, j, trie[k][g[i + 1][j] - 'A' + 1], true, true)); 
        }
        if(i + 1 < n && trie[k][0] != -1 && trie[root][g[i + 1][j] - 'A' + 1] != -1) { 
            ret = min(ret, 1 + func(i + 1, j, trie[root][g[i + 1][j] - 'A' + 1], true, true));
        }
        if(j     > 0 && trie[k][g[i][j - 1] - 'A' + 1] != -1 && go_left) { 
            ret = min(ret, 1 + func(i, j - 1, trie[k][g[i][j - 1] - 'A' + 1], true, false)); 
        }
        if(j     > 0 && trie[k][0] != -1 && trie[root][g[i][j - 1] - 'A' + 1] != -1 && go_left) { 
            ret = min(ret, 1 + func(i, j - 1, trie[root][g[i][j - 1] - 'A' + 1], true, false));
        }
        if(j + 1 < m && trie[k][g[i][j + 1] - 'A' + 1] != -1 && go_right) { 
            ret = min(ret, 1 + func(i, j + 1, trie[k][g[i][j + 1] - 'A' + 1], false, true));
        } 
        if(j + 1 < m && trie[k][0] != -1 && trie[root][g[i][j + 1] - 'A' + 1] != -1 && go_right) { 
            ret = min(ret, 1 + func(i, j + 1, trie[root][g[i][j + 1] - 'A' + 1], false, true)); 
        } 
        if(i == n - 1) { 
            ret = min(ret, (trie[k][0] == -1 ? inf : 0)); 
        }
        return ret; 
    };
    int ret = inf; 
    for(int j = 0; j < m; j++) { 
        if(trie[root][g[0][j] - 'A' + 1] == -1) continue;
        ret = min(ret, 1 + func(0, j, trie[root][g[0][j] - 'A' + 1], true, true)); 
    }
    if(ret == inf) puts("impossible"); 
    else cout << ret << '\n';
    return 0; 
}

/* Find the shortest path that containing all words in the dictionary */

