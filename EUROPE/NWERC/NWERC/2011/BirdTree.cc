#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int tc, a, b, den, num;
    char c; 
    cin >> tc;
    while (tc--)
    {
        cin >> a >> c >> b;  
        string ret; 
        while(a > 1 || b > 1)
        {
            if(a > b)
            {
                cout << "R"; 
                a = a - b;
            }
            else 
            {
                cout << "L";  
                b = b - a; 
            }
            swap(a, b); 
        }
        cout << '\n'; 
    }
    return 0;
}