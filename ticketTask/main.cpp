#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Ticket {
    string category;
    string issueType;
    string description;
    bool resolved;
};

vector<string> loadIssueCategories(const string& filePath) {
    vector<string> categories;
    ifstream file(filePath);
    if (file.is_open()) {
        string category;
        while (getline(file, category)) {
            categories.push_back(category);
        }
        file.close();
    }
    return categories;
}

int getValidInput(int minValue, int maxValue) {
    int choice;
    while (true) {
        cout << "Your choice (" << minValue << "-" << maxValue << "): ";
        if (cin >> choice) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (choice >= minValue && choice <= maxValue) {
                break;
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Invalid input. Please enter a valid choice.\n";
    }
    return choice;
}

string getValidStringInput() {
    string input;
    cin.ignore();
    while (true) {
        cout << "Enter your input: ";
        getline(cin, input);
        if (!input.empty()) {
            break;
        }
        cout << "Invalid input. Please enter a non-empty value.\n";
    }
    return input;
}

void createTicket(const vector<string>& categories) {
    cout << "Welcome to the Technical Support Ticketing System!\n";
    for (size_t i = 0; i < categories.size(); ++i) {
        cout << i + 1 << ". " << categories[i] << endl;
    }

    int categoryChoice = getValidInput(1, categories.size());

    string category = categories[categoryChoice - 1];

    cout << "Please select an issue type for " << category << ":" << endl;
    string issueType = getValidStringInput();

    cout << "Please describe the issue in detail:" << endl;
    string description = getValidStringInput();

    Ticket newTicket{category, issueType, description, false};

    cout << "\nTicket Created:\n";
    cout << "Category: " << newTicket.category << endl;
    cout << "Issue Type: " << newTicket.issueType << endl;
    cout << "Description: " << newTicket.description << endl;
}

int main() {
    vector<string> issueCategories = loadIssueCategories("issue_categories.txt");
    if (issueCategories.empty()) {
        cout << "Error: The issue_categories.txt file is empty or cannot be opened.\n";
        return 1;
    }

    createTicket(issueCategories);
    return 0;
}

