#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10 
string s,t;
int carry(int x)
{
     if(x > 9) return x - 10; 
     if(x < 0) return x + 10;  
     return x; 
}
string calc(string a, string b)
{
    int n = a.length();
    int curr = -1; 
    for(int i = 0; i < n; i++)
    {
        int tot = (a[i] - '0') + (b[i] - '0');
        if(curr == i)
        {
             tot += 1; 
        }
        if(tot >= 10) curr = i + 1; 
    }
    string xa = a; 
    for(int i = 0; i < curr; i++)
    {
         while(xa[i] != '0')
         {
             xa[i] = (char) (carry(xa[i] - '0' + 1) + '0'); 
             b[i] =  (char) (carry(b[i]  - '0' + 1) + '0'); 
         }
    }
    if(curr != -1) xa[curr] = (carry(xa[curr] - '0' +  1) + '0'); 
    string res(n, 0);
    for(int i = 0; i < n; i++)
    {
        res[i] += xa[i] - a[i];
        if(res[i] < 0 && i + 1 < n)
        {
            res[i + 1]--; 
            res[i] += ('0' + 10); 
        }
    }
    for(int i = 0; i < n; i++)
    {
        if(res[i] == NULL) res[i] = '0'; 
    }
    return res;
}
signed main(void)
{
     cin >> s >> t; 
     reverse(s.begin(), s.end());
     reverse(t.begin(), t.end()); 
     while(s.size() < t.size()) s.push_back('0');
     while(t.size() < s.size()) t.push_back('0'); 
     s.push_back('0');
     t.push_back('0'); 
     string a = calc(s, t); 
     string b = calc(t, s); 
     reverse(a.begin(), a.end());
     reverse(b.begin(), b.end()); 
     a = min(a, b);
     reverse(a.begin(), a.end());
     while(a.size() > 1 && a.back() == '0') a.pop_back();
     reverse(a.begin(), a.end()); 
     cout << a << '\n'; 
     return 0; 
}