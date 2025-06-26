#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int M, N;
    cin >> M >> N; 
    vector<int>vis(M + 1); 
    for(int i = 0; i < N; i++)
    {
        int x; 
        cin >> x; 
        vis[x] = 1; 
    }
    vector<string>rete, retc;
    for(int i = 1; i <= M; i++)
    {
        if(vis[i])
        {
            int j = i + 1; 
            while(j <= M && vis[j]) j++; 
            string ret = to_string(i); 
            if(i + 1 < j) ret += "-" + to_string(j - 1); 
            rete.push_back(ret); 
            i = j - 1; 
        }
        else 
        {
            int j = i + 1;
            while (j <= M && !vis[j]) j++;
            string ret = to_string(i);
            if (i + 1 < j) ret += "-" + to_string(j - 1);
            retc.push_back(ret);
            i = j - 1;
        }
    }
    cout << "Errors: "; 
    for(int i = 0; i < rete.size(); i++)
    {
        cout << rete[i] << (i == rete.size() - 2 ? " and " : (rete.size() == i + 1 ? "\n" : ", ")); 
    }
    cout << "Correct: ";
    for (int i = 0; i < retc.size(); i++)
    {
        cout << retc[i] << (i == retc.size() - 2 ? " and " : (retc.size() == i + 1 ? "\n" : ", "));
    }
    return 0;
}