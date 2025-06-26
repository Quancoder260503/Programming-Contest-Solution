#include "bits/stdc++.h"

using namespace std; 
const int M = 14;
int64_t fact[M];  

int main(void)
{
    int Q;
    string S; 
    fact[0] = 1; 
    for(int i = 1; i < M; i++) fact[i] = fact[i - 1] * i; 
    //cout << fact[2] << '\n'; 
    while(getline(cin, S))
    {
        vector<int>arr; 
        for(int i = 0; i < S.length(); i++)
        {
            string curr; 
            while(i < S.length() && S[i] != ' ') 
            {
                curr += S[i]; 
                i++; 
            }
            arr.push_back(stoi(curr)); 
        }
        int N = arr.size(); 
        cin >> Q; 
        int64_t ret = 0;
        vector<int> vis(N + 1);
        for(int i = 0; i < arr.size(); i++)
        {
            for(int j = 1; j < arr[i]; j++) if(!vis[j]) 
            {
                ret += fact[N - i - 1];
            }
            vis[arr[i]] = 1; 
        }
        cout << ret + 1 << '\n'; 
        fill(vis.begin(), vis.end(), 0); 
        for(int i = 0; i < N; i++) 
        {
            for(int j = 1; j <= N; j++)
            {
                if(vis[j]) continue; 
                if(fact[N - i - 1] < Q)
                {
                    Q = Q - fact[N - i - 1]; 
                }
                else 
                {
                    vis[j] = 1; 
                    cout << j << " "; 
                    break; 
                }
            }
        }
        cout << '\n';
        break;  
    }
    return 0; 
}