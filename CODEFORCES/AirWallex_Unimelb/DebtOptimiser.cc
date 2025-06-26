#include <bits/stdc++.h>
 
using namespace std;
 
struct Transaction {
    string payer, payee;
    int amount;
};
 
vector<Transaction> settleDebts(const vector<tuple<string, string, int>>& debts) {
    unordered_map<string, int> balance;
 
    for (const auto& [payer, payee, amount] : debts) {
        balance[payer] -= amount;
        balance[payee] += amount;
    }
 
    vector<pair<string, int>> debtors, creditors;
    for (const auto& [person, amt] : balance) {
        if (amt < 0) debtors.emplace_back(person, -amt);
        else if (amt > 0) creditors.emplace_back(person, amt); 
    } 
    vector<Transaction> transactions;
 
    while (!debtors.empty() && !creditors.empty()) {
        auto& [debtor, debtAmt] = debtors.back();
        auto& [creditor, creditAmt] = creditors.back();
 
        int settleAmount = min(debtAmt, creditAmt);
        transactions.push_back({debtor, creditor, settleAmount});
 
        debtAmt -= settleAmount;
        creditAmt -= settleAmount;
 
        if (debtAmt == 0) debtors.pop_back();
        if (creditAmt == 0) creditors.pop_back();
    }
 
    return transactions;
}
 
int main() {
    int n;
    cin >> n;
 
    vector<tuple<string, string, int>> debts(n);
    for (int i = 0; i < n; i++) {
        string payer, payee;
        int amount;
        cin >> payer >> payee >> amount;
        debts[i] = make_tuple(payer, payee, amount);
    }
 
    vector<Transaction> result = settleDebts(debts);
    cout << result.size() << '\n'; 
    sort(result.begin(), result.end(), [&](Transaction a, Transaction b) { 
     if(a.payer != b.payer) return a.payer < b.payer; 
     if(a.payee != b.payee) return a.payee < b.payee; 
     return a.amount < b.amount; 
    }); 
 
    for (const auto& [payer, payee, amount] : result) {
        cout << payer << " " << payee << " " << amount << "\n";
    }
 
    return 0;
}