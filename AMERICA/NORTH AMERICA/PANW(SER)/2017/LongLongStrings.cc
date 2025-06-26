#include "bits/stdc++.h"

using namespace std; 


struct operation
{
    char ops; 
    int64_t idx;
    char c = 'A'; 
    bool operator == (const operation &other) const
    {
        return ops == other.ops && idx == other.idx && c == other.c; 
    }
}; 

void f(vector<operation>&p)
{
    for(int i = 0; i < (int) p.size(); i++) for(int j = i; j > 0; j--)
    {
        if(p[j - 1].ops == 'I' && p[j].ops == 'I' && p[j - 1].idx >= p[j].idx)
        {
            swap(p[j - 1], p[j]);
            p[j].idx++; 
        }
        else if(p[j - 1].ops == 'D' && p[j].ops == 'D' && p[j - 1].idx <= p[j].idx)
        {
            swap(p[j - 1], p[j]); 
            p[j - 1].idx++; 
        }
        else if(p[j - 1].ops == 'I' && p[j].ops == 'D')
        {
            if(p[j - 1].idx > p[j].idx)
            {
                swap(p[j], p[j - 1]); 
                p[j].idx--; 
            }
            else if(p[j - 1].idx < p[j].idx)
            {
                swap(p[j], p[j - 1]); 
                p[j - 1].idx--; 
            }
            else 
            {
                p.erase(p.begin() + j - 1, p.begin() + j + 1); 
                i = i - 2; 
                break; 
            }
        }
        else break; 
    }
    return; 
}

int main(void)
{
    vector<vector<operation>>prog(2); 
    for(int i = 0; i < 2; i++)
    {
        for (;;)
        {
            string line;
            getline(cin, line);
            stringstream ss(line);
            string word;
            ss >> word;
            if (word == "E")  break;
            operation curr;
            if (word == "I")
            {
                curr.ops = word[0];
                ss >> word;
                curr.idx = stoll(word);
                ss >> word;
                curr.c = word[0];
            }
            else
            {
                curr.ops = word[0]; 
                ss >> word;
                curr.idx = stoll(word);
            }
            prog[i].push_back(curr); 
        }
    }
    f(prog[0]);
    f(prog[1]); 
    cout << (1 xor (prog[0] == prog[1])) << '\n'; 
    return 0; 
}