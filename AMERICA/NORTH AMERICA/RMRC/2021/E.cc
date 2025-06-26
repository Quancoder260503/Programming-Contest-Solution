#include "bits/stdc++.h"
using namespace std;
const int MAXN = 2000;
int n;
int arr[MAXN];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    sort(arr + 1, arr + n + 1);
    reverse(arr + 1, arr + n + 1);
    int sum = 0;
    for (int i = 1; i <= n / 2; i++)
    {
        sum += arr[i];
    } 
    for (int i = n / 2 + 1; i <= n; i++)
    {
        sum += (arr[i] / 2);
    }
    cout << sum << '\n';
    return 0;
}