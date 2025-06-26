#include "bits/stdc++.h"

using namespace std;

vector<int>ok_digits; 

int64_t find_low(string S)
{
    int N = S.length(); 
    if(ok_digits.size() == 0) return -1;
    for(int i = ok_digits.size() - 1; i >=0; i--)
    {
        if(ok_digits[i] < S[0] - '0')
        {
            int64_t ret = ok_digits[i]; 
            int dig = ok_digits[ok_digits.size() - 1];
            for(int j = 0; j < N - 1; j++) ret = ret * 10LL + dig; 
            return ret;
        }
    }
    int dig = ok_digits[ok_digits.size() - 1];
    int64_t ret = 0; 
    for(int i = 0; i < N - 1; i++)
    {
        ret = ret * 10LL + dig;
    }
    return ret;
}

int64_t find_upp(string S)
{
    int N = S.length();
    if (ok_digits.size() == 0) return -1;
    for (int i = 0; i < ok_digits.size(); i++)
    {
        if (S[0] - '0' < ok_digits[i])
        {
            int64_t ret = ok_digits[i];
            int dig = ok_digits[0];
            for (int j = 0; j < N - 1; j++) ret = ret * 10LL + dig;
            return ret;
        }
    }
    if(ok_digits[0] == 0 && ok_digits.size() < 2) return -1; 
    int64_t dig = ok_digits[0];
    int64_t ret = ok_digits[0] == 0 ? ok_digits[1] : ok_digits[0];
    for (int i = 0; i < N; i++)
    {
        ret = ret * 10LL + dig;
    }
    return ret;
}

int main(void)
{
    string S; 
    while(cin >> S)
    {
        ok_digits.clear(); 
        for (int i = 0; i < 10; i++) if (S.find(i + '0') == -1)
        {
            ok_digits.push_back(i);
        }
        int64_t reta = find_low(S); 
        int64_t retb = find_upp(S); 
        //cout << reta << " " << retb << '\n'; 
        if(reta == -1 && retb == -1)
        {
            cout << "Impossible" << '\n'; 
        }
        else if(reta == -1)
        {
            cout << retb << '\n'; 
        }
        else if(retb == -1)
        {
            cout << reta << '\n'; 
        }
        else
        {
            int64_t da = stoll(S) - reta; 
            int64_t db = retb - stoll(S); 
            if(da == db) cout << reta << " " << retb << '\n';
            else if(da < db) cout << reta << '\n'; 
            else cout << retb << '\n'; 
        }
    } 
    return 0;
}