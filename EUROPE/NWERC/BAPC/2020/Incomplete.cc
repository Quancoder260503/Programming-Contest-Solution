#include "bits/stdc++.h"

using namespace std;
const int maxf = 1e6; 

int arr[maxf], to[maxf]; 

int main(void)
{
    int N; 
    while(cin >> N)
    {
        for(int i = 1; i <= N; i++) 
        {
            cin >> arr[i];
            to[arr[i]] = i;  
        }
        cout << 3 << '\n';
        for(int i = 1; i <= N / 2; i += N / 4)
        {
            vector<int>rx, ry; 
            map<int, int>vis; 
            for(int j = i; j < i + N / 4; j++) 
            {
                vis[to[j]] = 1; 
                rx.push_back(j); 
                ry.push_back(to[j]); 
            }
            for(int j = i; j < i + N / 4; j++) if(!vis[j])
            {
                rx.push_back(arr[j]); 
                ry.push_back(j); 
                vis[j] = 1;
            }
            for(int j = 1; j <= N && rx.size() < N / 2; j++) if(!vis[j])
            {
                rx.push_back(arr[j]); 
                ry.push_back(j); 
            }
            sort(rx.begin(), rx.end()); 
            sort(ry.begin(), ry.end()); 
            for(int j = 0; j < N / 2; j++)
            {
                arr[ry[j]] = rx[j];
                to[rx[j]] = ry[j]; 
                cout << ry[j] << " "; 
            }
            cout << '\n'; 
        }
        for(int i = N / 2 + 1; i <= N; i++) cout << i << " "; 
        cout << '\n';  
    }
    return 0;
}