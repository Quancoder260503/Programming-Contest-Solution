#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int n; 
    cin >> n; 
    vector<int>state(n);
    for(int i = 0; i < n; i++) 
    {
        char c; 
        cin >> c; 
        state[i] = (c == 'T'); 
    }
    char c;
    vector<int>states;  
    while(cin >> c)
    {
        if(c == '*')
        {
            states[states.size() - 2] &= states[states.size() - 1];
            states.pop_back(); 
        }
        else if(c == '+')
        {
            states[states.size() - 2] |= states[states.size() - 1];
            states.pop_back(); 
        }
        else if(c == '-')
        {
            states[states.size() - 1] = !states[states.size() - 1];
        }
        else 
        {
            states.push_back(state[c - 'A']); 
        }
    }
    cout << (states.back() ? 'T' : 'F') << '\n'; 
    return 0;
}