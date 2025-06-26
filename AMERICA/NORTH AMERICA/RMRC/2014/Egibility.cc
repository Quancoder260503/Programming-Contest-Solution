#include "bits/stdc++.h"

using namespace std;

int main(void) {
    int tc, N, M;
    string s, name, word, dob, doe, course; 
    cin >> tc; 
    cin.ignore(); 
    while(tc--) {
        getline(cin, s); 
        stringstream ss(s); 
        ss >> name >> doe >> dob >> course;
        if(stoi(doe.substr(0, 4)) >= 2010 || stoi(dob.substr(0, 4)) >= 1991) { 
            cout << name << " eligible\n"; 
        }
        else if(stoi(course) > 40) { 
            cout << name << " ineligible\n"; 
        }
        else { 
            cout << name << " coach petitions\n"; 
        }
    }
    return 0;
}