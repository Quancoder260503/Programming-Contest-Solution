#include "bits/stdc++.h"
using namespace std;
int main(void)
{
    int N, K; 
    while (cin >> N >> K)
    {
        puts( (K / N + (K % N > N / 2) + 1) & 1 ? "up" : "down");  
    }
    return 0;
}