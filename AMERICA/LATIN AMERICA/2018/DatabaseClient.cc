#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int N; 
    while(cin >> N)
    {
        map<pair<string, string>, int>ctr; 
        for(int i = 0; i < N; i++)
        {
            string S; 
            cin >> S; 
            string name; 
            string addr; 
            int j;
            for(j = 0; j < S.length(); j++)
            {
                if(S[j] == '@' || S[j] == '+') break; 
                if(S[j] != '.') name += S[j]; 
            }
            while(j < S.length() && S[j] != '@') j++; 
            j++;
            while(j < S.length()) addr += S[j++]; 
            //cout << name << " " << addr << '\n'; 
            ctr[{name, addr}] = 1; 
        }
        cout << ctr.size() << '\n'; 
    }
    return 0;
}