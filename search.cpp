#include "search.h"
#include <iostream>
#include <fstream>
#include<string>
#include <mutex>

using namespace std;

mutex coutMutex;

const string BOLD_YELLOW = "\033[1;33m";
const string RESET = "\033[0m";

void searchInFile(const string& filename, const string& word) {
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    int lineNumber = 1;

    while (getline(file, line)) {
        size_t pos = line.find(word);
        if (pos != string::npos) {
            string highlightedLine = "";
            size_t start = 0;

            while ((pos = line.find(word, start)) != string::npos) {
                highlightedLine += line.substr(start, pos - start); 
                highlightedLine += BOLD_YELLOW + word + RESET;    
                start = pos + word.length();                       
            }
            highlightedLine += line.substr(start); 

            {
                lock_guard<mutex> lock(coutMutex); 
                cout << filename << " : Line " << lineNumber << " -> " << highlightedLine << endl;
            }
        }
        lineNumber++;
    }
}