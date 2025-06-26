#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    string alpha, a;
    cin >> alpha >> a; 
    int N = a.length(); 
    set<string>c; 
    for(int i = 0; i <= N; i++)
    {
        string p, s; 
        p = a.substr(0, i);
        if(i < N) 
        {
            s = a.substr(i + 1, N - i);
            c.insert(p + s);
        }
        s = a.substr(i, N - i); 
        for (char ch : alpha)
        {
            if(i < N && ch != a[i])
            {
                char str = a[i];
                a[i] = ch;
                c.insert(a);
                a[i] = str;
            }
            c.insert(p + ch + s);
        }
    }
    for(auto v : c) cout << v << '\n'; 
    return 0; 
}