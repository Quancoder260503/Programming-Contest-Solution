#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int N; 
    while (cin >> N)
    {
        for(int i = 0; i < N; i++)
        {
            int K; 
            cin >> K; 
            cout << K << '\n';
            for(int j = 0; j < K; j++) 
            {
                string S; 
                cin >> S; 
                cout << S << '\n'; 
            } 
            return 0; 
        }
    }
    return 0;
}