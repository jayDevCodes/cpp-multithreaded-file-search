#include "search.h"
#include <iostream>
#include <fstream>

using namespace std;

void searchInFile(const string& filename, const string& word) {
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    int lineNumber = 1;

    while (getline(file, line)) {
        if (line.find(word) != string::npos) {
            cout << filename << " : Line " << lineNumber << " -> " << line << endl;
        }
        lineNumber++;
    }
}