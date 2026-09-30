// * Project Title: Phone Directory System
// * Course: Computer Programming (2025-2026) 
//______________________________________________________________________
 

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// Phase 1: Forming the matrix structure and basic data
const int MAX_CONTACTS = 100;
const string FILENAME = "contacts.txt";

struct Contact {
    string name;  // [cite: 28]
    string phone; // [cite: 30]
};

Contact directory[MAX_CONTACTS];
int contactCount = 0;

// Convert the text to lowercase so the formatting is correct. (Case-Insensitive)
string toLower(string s) {
    for (int i = 0; i < s.length(); i++) s[i] = tolower(s[i]);
    return s;
}

bool containsIgnoreCase(const string& text, const string& pattern) {
    string lowerText = toLower(text);
    string lowerPattern = toLower(pattern);
    return lowerText.find(lowerPattern) != string::npos;
}

// Phase 3: Saving and Loading Files [cite: 14, 19]
void saveToFile() {
    ofstream file(FILENAME);
    if (file.is_open()) {
        for (int i = 0; i < contactCount; i++) {
            file << directory[i].name << "|" << directory[i].phone << "\n";
        }
        file.close();
    }
}

void loadFromFile() {
    ifstream file(FILENAME);
    contactCount = 0;
    if (file.is_open()) {
        string line;
        while (getline(file, line) && contactCount < MAX_CONTACTS) {
            size_t pos = line.find("|");
            if (pos != string::npos) {
                directory[contactCount].name = line.substr(0, pos);
                directory[contactCount].phone = line.substr(pos + 1);
                contactCount++;
            }
        }
        file.close();
    }
}

// Phase 4: Research and Sort 
void displaySorted() {
    if (contactCount == 0) { 
        cout << "Directory is empty.\n"; 
        return; 
    }
    
    Contact temp[MAX_CONTACTS];
    for (int i = 0; i < contactCount; i++) temp[i] = directory[i];

    // A simple and reliable arrangement that doesn't contain mistakes or errors. Runtime
    sort(temp, temp + contactCount, [](const Contact& a, const Contact& b) {
        string nameA = a.name;
        string nameB = b.name;
        for(auto &c : nameA) c = tolower(c);
        for(auto &c : nameB) c = tolower(c);
        return nameA < nameB;
    });

    cout << "\n--- Sorted Contacts ---\n";
    for (int i = 0; i < contactCount; i++) {
        cout << i + 1 << ". " << temp[i].name << " - " << temp[i].phone << endl;
    }
}

// Submenus as in PDF [cite: 31, 33, 35, 37]
void addContactMenu() {
    int choice;
    while (true) {
        cout<< "\n[Add Contact Menu]\n1. Enter Name and Phone Number\n2. Quit\nChoice: ";
        
        cin >> choice;
        if (choice == 2) break;
        if (choice == 1) {
            if (contactCount < MAX_CONTACTS) {
                cout << "Enter Name: "; cin >> ws; getline(cin, directory[contactCount].name);
                cout << "Enter Phone: "; getline(cin, directory[contactCount].phone);
                contactCount++;
                saveToFile();
                cout << "Contact Saved!\n";
            } else { cout << "Full!\n"; }
        }
    }
}


void displayMenu() {
    int choice;
    while (true) {
        cout << "\n[Display Menu]\n1. Search for Specific Contact\n2. Display Contact Sorted\n3. Display All Contacts\n4. Quit\nChoice: "; // [cite: 36]
        cin >> choice;
        if (choice == 4) break;
        switch (choice) {
            case 1: {
                string key;
                cout << "Search: "; cin >> ws; getline(cin, key);
                bool f = false;
                for (int i = 0; i < contactCount; i++) {
                    if (containsIgnoreCase(directory[i].name, key) || containsIgnoreCase(directory[i].phone, key)) {
                        cout << "Found: " << directory[i].name << " [" << directory[i].phone << "]\n";
                        f = true;
                    }
                }
                if (!f) cout << "Not found.\n";
                break;
            }
            case 2: displaySorted(); break;
            case 3:
                for (int i = 0; i < contactCount; i++) 
                    cout << i+1 << ". " << directory[i].name << " - " << directory[i].phone << endl;
                break;
        }
    }
}

void deleteMenu() {
    int choice;
    while (true) {
        cout << "\n[Delete Menu]\n1. Delete Specific Contact\n2. Delete all Contacts\n3. Quit\nChoice: "; // [cite: 38]
        cin >> choice;
        if (choice == 3) break;
        if (choice == 2) {
            contactCount = 0;
            saveToFile();
            cout << "Cleared.\n";
        } else if (choice == 1) {
            string key;
            cout << "To delete: "; cin >> ws; getline(cin, key);
            for (int i = 0; i < contactCount; i++) {
                if (directory[i].name == key || directory[i].phone == key) {
                    for (int j = i; j < contactCount - 1; j++) directory[j] = directory[j+1];
                    contactCount--;
                    saveToFile();
                    cout << "Deleted.\n";
                    break;
                }
            }
        }
    }
}

int main() {
    loadFromFile();
    int mainChoice;
    while (true) {
        cout << "\n--- Main View ---\n1. Add Contact\n2. Display Contact\n3. Delete Contacts\n4. Quit\nChoice: "; // [cite: 32]
        cin >> mainChoice;
        if (mainChoice == 4) break;
        switch (mainChoice) {
            case 1: addContactMenu(); break;
            case 2: displayMenu(); break;
            case 3: deleteMenu(); break;
        }
    }
    return 0;
}
// A wonderful ending (-_-)