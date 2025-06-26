#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    map<pair<int, int>, int>g; 
    function<int(int, int)>grundy = [&](int si, int sj) { 
        if(g.count({si, sj})) return g[{si, sj}]; 
        set<int>gr; 
        if(si - 2 >= 1  && sj + 1 <= 15) gr.insert(grundy(si - 2, sj + 1)); 
        if(si - 2 >= 1  && sj - 1 >= 1)  gr.insert(grundy(si - 2, sj - 1));
        if(si + 1 <= 15 && sj - 2 >= 1)  gr.insert(grundy(si + 1, sj - 2)); 
        if(si - 1 >= 1  && sj - 2 >= 1)  gr.insert(grundy(si - 1, sj - 2));
        int mex = 0; 
        while(gr.count(mex)) mex++; 
        return g[{si, sj}] = mex; 
    }; 
    int tc, ret;
    cin >> tc; 
    for(int i = 0, si, sj; i < tc; i++) {
        cin >> si >> sj;  
        ret = grundy(si, sj);
        cout << (ret ? "First" : "Second") << '\n';
    }
    return 0; 
}