#include "bits/stdc++.h"

using namespace std;
const int maxf = 1e6 + 2; 

int vis[maxf]; 
vector<int>oadj[maxf];
vector<pair<vector<int>, int>>g; 

int main(void)
{ 
    int N;
    while (cin >> N)
    {
        map<string, int>mp; 
        int ctr = 0; 
        auto get_dict = [&](string S)
        {
            if(mp.count(S)) return mp[S];
            return mp[S] = ctr++; 
        }; 
        cin.ignore(); 
        vector<int>top; 
        for (int i = 0; i < N; i++)
        {   
            string line; 
            getline(cin, line); 
            stringstream ss(line); 
            string word; 
            ss >> word; 
            if(word == "if")
            {
                bool is_and = false;
                vector<int>constr; 
                while(ss >> word)
                {
                    if(word == "and") is_and = true; 
                    else if (word == "then")
                    {
                        ss >> word; 
                        sort(constr.begin(), constr.end()); 
                        constr.erase(unique(constr.begin(), constr.end()), constr.end()); 
                        if(is_and)
                        {
                            g.push_back({constr, get_dict(word)}); 
                        }
                        else 
                        {
                            for(auto v : constr) oadj[v].push_back(get_dict(word)); 
                        }
                        break; 
                    }
                    else if (word != "or") 
                    {
                        constr.push_back(get_dict(word)); 
                    } 
                }
            }
            else 
            {
                top.push_back(get_dict(word)); 
            }
        }
        int ret = 0; 
        function<void(int)>doit = [&](int u)
        {
            if(vis[u]) return;
            ret++; 
            vis[u] = 1;
            for(auto v : oadj[u]) doit(v); 
            for(auto [v, to] : g)
            {
                int chk = 1; 
                for(auto x : v) chk = chk & (vis[x]); 
                if(chk) doit(to); 
            }
        };
        for(auto u : top) doit(u); 
        cout << ret << '\n'; 
    }
    return 0;
}