#include "bits/stdc++.h"

using namespace std; 

const int maxf = 2e5 + 10; 
vector<int>g[maxf]; 
string c; 
int n; 
string brackets = "()[]{}"; 
vector<int>vis; 

int dfs(int u, int p, stack<char>&stk) {
    if(brackets.find(c[u]) % 2 == 0) { 
        stk.push(c[u]); 
    }
    else if(stk.size() && brackets.find(stk.top()) + 1 == brackets.find(c[u])) { 
        stk.pop(); 
    }
    else return 0; 
    int ret = stk.empty(); 
    for(auto v : g[u]) if(v != p) {
       ret += dfs(v, u, stk);
    }
    if(brackets.find(c[u]) % 2 == 1) {
        stk.push(brackets[brackets.find(c[u]) - 1]);
    }
    else { 
        stk.pop(); 
    }
    return ret; 
}

int main(void) { 
    cin >> n >> c; 
    for(int i = 0, u, v; i < n - 1; i++) { 
        cin >> u >> v; 
        g[--u].push_back(--v);
        g[v].push_back(u); 
    }
    stack<char>stk; 
    int ret = 0;
    for(int i = 0; i < n; i++) { 
        while(stk.size()) stk.pop(); 
        ret += dfs(i, -1, stk); 
    }
    cout << ret << '\n'; 
    return 0; 
}