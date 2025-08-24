#include <bits/stdc++.h>
using namespace std;

struct Transaction {
    string type;
    string category;
    double amount;
    string date;
};

class FinanceTracker {
private:
    vector<Transaction> transactions;
    const string filename = "finance_data.txt";

public:
    void addTransaction(string type, string category, double amount, string date) {
        transactions.push_back({type, category, amount, date});
        cout << "Transaction added successfully.\n";
    }

    void showTransactions() {
        cout << "\n=== All Transactions ===\n";
        if (transactions.empty()) {
            cout << "No transactions recorded.\n";
            return;
        }
        for (size_t i = 0; i < transactions.size(); i++) {
            cout << i+1 << ". [" << transactions[i].type << "] "
                 << transactions[i].category << " | $"
                 << transactions[i].amount << " | " 
                 << transactions[i].date << endl;
        }
    }

    void sortByAmount() {
        sort(transactions.begin(), transactions.end(), 
             [](Transaction &a, Transaction &b) {
                 return a.amount > b.amount;
             });
        cout << "Transactions sorted by amount (descending).\n";
    }

    void searchCategory(string category) {
        cout << "\n=== Search Results for Category: " << category << " ===\n";
        bool found = false;
        for (auto &t : transactions) {
            if (t.category == category) {
                cout << "[" << t.type << "] " << t.category 
                     << " | $" << t.amount << " | " << t.date << endl;
                found = true;
            }
        }
        if (!found) cout << "No transactions found.\n";
    }

    void filterExpenses(double minAmount) {
        cout << "\n=== Expenses over $" << minAmount << " ===\n";
        bool found = false;
        for (auto &t : transactions) {
            if (t.type == "Expense" && t.amount > minAmount) {
                cout << "[" << t.type << "] " << t.category 
                     << " | $" << t.amount << " | " << t.date << endl;
                found = true;
            }
        }
        if (!found) cout << "No matching expenses found.\n";
    }

    void saveToFile() {
        ofstream file(filename);
        if (!file) {
            cout << "Error saving file.\n";
            return;
        }
        for (auto &t : transactions) {
            file << t.type << "," << t.category 
                 << "," << t.amount << "," << t.date << "\n";
        }
        file.close();
        cout << "Data saved to file.\n";
    }

    void loadFromFile() {
        ifstream file(filename);
        if (!file) {
            cout << "No saved data found.\n";
            return;
        }
        transactions.clear();
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string type, category, amountStr, date;
            getline(ss, type, ',');
            getline(ss, category, ',');
            getline(ss, amountStr, ',');
            getline(ss, date, ',');
            transactions.push_back({type, category, stod(amountStr), date});
        }
        file.close();
        cout << "Data loaded from file.\n";
    }

    void monthlySpendingChart() {
        map<string, double> monthlyTotals;
        for (auto &t : transactions) {
            if (t.type == "Expense") {
                string month = t.date.substr(0, 7);
                monthlyTotals[month] += t.amount;
            }
        }
        cout << "\n=== Monthly Spending Chart ===\n";
        for (auto &entry : monthlyTotals) {
            cout << entry.first << " | $" << entry.second << " | ";
            int bars = (int)(entry.second / 50);
            for (int i = 0; i < bars; i++) cout << "#";
            cout << endl;
        }
    }
};

int main() {
    FinanceTracker tracker;
    tracker.loadFromFile();

    int choice;
    string type, category, date;
    double amount;

    while (true) {
        cout << "\n=== Personal Finance Tracker ===\n";
        cout << "1. Add Transaction\n";
        cout << "2. Show All Transactions\n";
        cout << "3. Sort by Amount\n";
        cout << "4. Search by Category\n";
        cout << "5. Filter Expenses > $100\n";
        cout << "6. Show Monthly Spending Chart\n";
        cout << "7. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter type (Income/Expense): ";
                cin >> type;
                cout << "Enter category: ";
                cin >> category;
                cout << "Enter amount: ";
                cin >> amount;
                cout << "Enter date (YYYY-MM-DD): ";
                cin >> date;
                tracker.addTransaction(type, category, amount, date);
                break;
            case 2:
                tracker.showTransactions();
                break;
            case 3:
                tracker.sortByAmount();
                break;
            case 4:
                cout << "Enter category to search: ";
                cin >> category;
                tracker.searchCategory(category);
                break;
            case 5:
                tracker.filterExpenses(100);
                break;
            case 6:
                tracker.monthlySpendingChart();
                break;
            case 7:
                tracker.saveToFile();
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}
