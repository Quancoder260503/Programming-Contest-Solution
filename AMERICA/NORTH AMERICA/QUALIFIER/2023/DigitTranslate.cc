#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 2; 
int64_t ctr[maxf], dyn[maxf]; 
const int mod = 9302023; 

int main(void)
{
    string s; 
    cin >> s;
    s = " " + s;
    for(int i = 0; i < s.size(); i++) dyn[i] = INT32_MAX;
    dyn[0] = 0;
    ctr[0] = 1; 
    vector<string>digit = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}; 
    for(int i = 1; i < s.size(); i++)
    {
        dyn[i] = dyn[i - 1] + 1;
        ctr[i] = ctr[i - 1]; 
        for(int j = 0; j < digit.size(); j++)
        {
            if(i < digit[j].size()) continue; 
            auto u = digit[j]; 
            auto v = s.substr(i - u.size() + 1, u.size());
            if(u != v) continue;  
            if(dyn[i] > dyn[i - u.size()] + 1)
            {
                dyn[i] = dyn[i - u.size()] + 1;
                ctr[i] = ctr[i - u.size()]; 
            }
            else if(dyn[i] == dyn[i - u.size()] + 1)
            {
                ctr[i] += ctr[i - u.size()]; 
                ctr[i] %= mod; 
            }
        }
    }
    cout << dyn[s.size() - 1] << '\n' << ctr[s.size() - 1] << '\n'; 
    return 0; 
}