#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10 
#define LEN 25 
signed main(void)
{
    string pattern;
    for(int i = 0; i < LEN; i++)
    {
         pattern += (rand() % 2 == 0 ? '1' : '0'); 
    }
    int curr = 0; 
    string rep; 
    while(true)
    {
        char c; 
        cin >> c;
        rep += c; 
        if(rep.length() >= pattern.length()) 
        {
            if(equal(pattern.rbegin(), pattern.rend(), rep.rbegin()))
            {
                cout << "! " << rep.length() - pattern.length() << '\n'; 
                return 0; 
            }
        }
        if(curr < pattern.length() && pattern[curr] != c)
        { 
               cout << "? flip" << '\n'; 
               cin >> c;
        }
        cout << "? right" << '\n'; 
        curr += 1; 
    }
    return 0;
}