#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>arr(N);  
        list<int>q;
        vector<vector<int>>turns; 
        vector<list<int>::iterator>qit; 
        vector<int>vis(N, true); 
        set<int>dyn; 
        for(int i = 0; i < N; i++)
        {
            cin >> arr[i];       
            q.push_back(i); 
            qit.push_back(prev(q.end()));     
            dyn.insert(i);  
        }
        while(dyn.size())
        {
            set<int>ndyn;
            vector<int>turn;  
            for(auto at : dyn)
            {
                auto it = qit[at]; 
                if(it != q.begin()     && arr[*it] < arr[*prev(it)]) vis[at] = false;
                if(it != prev(q.end()) && arr[*it] < arr[*next(it)]) vis[at] = false; 
                if(!vis[at])
                {
                    turn.push_back(at); 
                    if(it != q.begin())     ndyn.insert(*prev(it)); 
                    if(it != prev(q.end())) ndyn.insert(*next(it)); 
                }
            }
            for(auto at : dyn) if(!vis[at]) q.erase(qit[at]); 
            if(turn.size()) turns.push_back(turn); 
            dyn.clear(); 
            for(auto v : ndyn) if(vis[v]) dyn.insert(v); 
        }
        turns.push_back(vector<int>(q.begin(), q.end())); 
        cout << turns.size() - 1 << '\n'; 
        for(auto it : turns)
        {
            for(auto v : it) cout << arr[v] << " "; 
            cout << '\n'; 
        }
    }
    return 0;
}