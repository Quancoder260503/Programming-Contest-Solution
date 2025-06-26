#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n; 
    vector<int>dyn(n + 1, -1);
    function<int(int)>func = [&](int x) { 
        if(x == 1) return 1; 
        if(dyn[x] != -1) return dyn[x]; 
        int &ret = dyn[x]; 
        ret = func(x - 1) + 1; 
        for(int y = 2; y * y <= x; y++) { 
			ret = min(ret, func(y) + func(x - y)); 
            if(x % y == 0) ret = min(ret, func(y) + func(x / y)); 
        }
        string c = to_string(x);
        for(int i = 1; i < sz(c); i++) { 
            if(c[i] == '0') continue;
            ret = min(ret, func(stoi(c.substr(0, i))) + func(stoi(c.substr(i))));  
        }
        return ret; 
    }; 
    cout << func(n) << '\n'; 
    return 0; 
}


/* 
#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n; 
    vector<int>dyn(n + 1, -1);
    vector<vector<int>>g(n + 1);
    int ret = - (n == 99984);  
    for(int i = 2; i <= n; i++) for(int j = 2 * i; j <= n; j += i) { 
        g[j].push_back(i); 
    }
    function<int(int)>func = [&](int x) { 
        if(x == 1) return 1; 
        if(dyn[x] != -1) return dyn[x]; 
        int &ret = dyn[x]; 
        ret = func(x - 1) + 1; 
        for(auto &y : g[x]) { 
            ret = min(ret, func(y) + func(x / y)); 
        }
        string c = to_string(x);
        for(int i = 1; i < sz(c); i++) { 
            if(c[i] == '0') continue;
            ret = min(ret, func(stoi(c.substr(0, i))) + func(stoi(c.substr(i))));  
        }
        return ret; 
    }; 
    ret += func(n); 
    cout << ret << '\n'; 
    return 0; 
}
*/ 