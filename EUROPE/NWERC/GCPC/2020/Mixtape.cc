#include "bits/stdc++.h"
using namespace std;
int main(void)
{
    int N; 
    while(cin >> N)
    {
        for(int i = 0; i < N; i++)
        {
            int x; 
            cin >> x; 
            string c = to_string(i + 1000); 
            int ptr = x;
            while(ptr > 0)
            {
                ptr--; 
                c += '0'; 
            } 
            cout << c << " "; 
        }
        cout << '\n'; 
    }
    return 0; 
}