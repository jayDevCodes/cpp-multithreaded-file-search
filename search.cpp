#include "search.h"
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <regex>

using namespace std;

mutex coutMutex;

const string BOLD_YELLOW = "\033[1;33m";
const string RESET = "\033[0m";

void searchInFile(const string& filename, const regex& pattern) {
    ifstream file(filename);
    if (!file.is_open()) return;

    string line;
    int lineNumber = 1;

    while (getline(file, line)) {
        sregex_iterator iter(line.begin(), line.end(), pattern);
        sregex_iterator end;

        if(iter != end) {
            string highlightedLine = "";
            size_t start = 0;

            while (iter != end) {
                smatch match = *iter;
                highlightedLine += line.substr(start, match.position() - start); 
                highlightedLine += BOLD_YELLOW + match.str() + RESET;    
                start = match.position() + match.length();                       
                ++iter;
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