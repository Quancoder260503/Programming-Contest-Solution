#include "bits/stdc++.h"
using namespace std;
bool palin(string s) 
{
     int N = s.length();
     for(int i = 0; i < N / 2; i++)
     {
         if(s[i] != s[N - 1 - i]) return 0; 
     }
     return 1; 
}
signed main(void)
{
    string s;
    int good = 1; 
    cin >> s; 
    int N = s.length();
    for(int i = 0; i < N; i++)
    {
         for(int j = i; j < N; j++)
         {
             string curr;
             for(int k = i; k <= j; k++)
             {
                 curr += s[k]; 
             } 
             if( palin(curr) )
             { 
                good = good & ((j - i + 1) & 1); 
             }
         }
    }
    cout << (good ? "Odd." : "Or not.")<< '\n'; 
    return 0;
}