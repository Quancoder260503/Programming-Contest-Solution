#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int N, X; 
    cin >> N >> X;
    vector<double>rx(N);
    double sum = 0;  
    for(int i = 0; i < N; i++) 
    {
        cin >> rx[i]; 
        sum += rx[i] * rx[i]; 
    }
    if(sum != 0) sum = sqrt(1.0 * X * N / sum) ; 
    cout << fixed << setprecision(10); 
    for(int i = 0; i < N; i++) cout << rx[i] * sum << " "; 
    cout << '\n'; 
    return 0; 
}