#include "bits/stdc++.h"

using namespace std;

vector<int> prefix_function(const string &s)
{
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i)
    {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

int main(void)
{
    string S; 
    cin >> S; 
    int N = S.length(); 
    auto pi = prefix_function(S); 
    vector<int>ctr(N); 
    for(int i = 0; i + 1 < N; i++) ctr[pi[i]]++; 
    int j = N; 
    while(j > 0)
    {
        j = pi[j - 1]; 
        if(j == 0) break; 
        if(ctr[j] > 0)
        {
            cout << S.substr(0, j) << '\n'; 
            return 0; 
        }
    }
    cout << "Just a legend" << '\n'; 
    return 0; 
}