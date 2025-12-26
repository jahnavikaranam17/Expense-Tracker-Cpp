#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Expense {
    int id;
    char category[30];
    float amount;
    char date[15];

public:
    void getData() {
        cout << "\nEnter Expense ID: ";
        cin >> id;

        cout << "Enter Category: ";
        cin >> category;

        cout << "Enter Amount: ";
        cin >> amount;

        cout << "Enter Date (DD/MM/YYYY): ";
        cin >> date;
    }

    void showData() {
        cout << "\n----- Expense Details -----\n";
        cout << "ID: " << id;
        cout << "\nCategory: " << category;
        cout << "\nAmount: " << amount;
        cout << "\nDate: " << date << endl;
    }

    float getAmount() {
        return amount;
    }

    char* getCategory() {
        return category;
    }
};

class ExpenseManager {
public:

    void addExpense() {
        Expense e;
        e.getData();

        ofstream file("expenses.dat", ios::binary | ios::app);
        file.write((char*)&e, sizeof(e));
        file.close();

        cout << "\nExpense Saved Successfully!\n";
    }

    void showAll() {
        Expense e;
        ifstream file("expenses.dat", ios::binary);

        if(!file) {
            cout << "\nNo expenses found!\n";
            return;
        }

        cout << "\n===== All Saved Expenses =====\n";
        while(file.read((char*)&e, sizeof(e))) {
            e.showData();
        }

        file.close();
    }

    void showTotalSpending() {
        Expense e;
        ifstream file("expenses.dat", ios::binary);

        if(!file) {
            cout << "\nNo expenses found!\n";
            return;
        }

        float total = 0;
        while(file.read((char*)&e, sizeof(e))) {
            total += e.getAmount();
        }

        cout << "\n===== TOTAL SPENDING =====\n";
        cout << "Total Amount Spent = " << total << endl;

        file.close();
    }

    void showCategoryWise() {
        Expense e;
        ifstream file("expenses.dat", ios::binary);

        if(!file) {
            cout << "\nNo expenses found!\n";
            return;
        }

        float food = 0, travel = 0, shopping = 0, others = 0;

        while(file.read((char*)&e, sizeof(e))) {

            if(strcmp(e.getCategory(), "Food") == 0 || strcmp(e.getCategory(), "food") == 0)
                food += e.getAmount();

            else if(strcmp(e.getCategory(), "Travel") == 0 || strcmp(e.getCategory(), "travel") == 0)
                travel += e.getAmount();

            else if(strcmp(e.getCategory(), "Shopping") == 0 || strcmp(e.getCategory(), "shopping") == 0)
                shopping += e.getAmount();

            else
                others += e.getAmount();
        }

        cout << "\n===== CATEGORY WISE SPENDING =====\n";
        cout << "Food: " << food << endl;
        cout << "Travel: " << travel << endl;
        cout << "Shopping: " << shopping << endl;
        cout << "Others: " << others << endl;

        file.close();
    }
};

int main() {
    ExpenseManager obj;
    int choice;

    while(true) {
        cout << "\n\n==== EXPENSE TRACKER MENU ====\n";
        cout << "1. Add Expense\n";
        cout << "2. View All Expenses\n";
        cout << "3. Show Total Spending\n";
        cout << "4. Show Spending By Category\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: obj.addExpense(); break;
            case 2: obj.showAll(); break;
            case 3: obj.showTotalSpending(); break;
            case 4: obj.showCategoryWise(); break;
            case 5: 
                cout << "\nExiting... Thanks!\n";
                return 0;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }
    }
}
