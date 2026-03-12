#include <iostream>
#include <thread>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <execution>
#include <regex>
#include "search.h"
using namespace std;

int main() {
    string path;
    cout <<"Enter file Path: ";
    cin >> path;

    vector<string> files;
    for (const auto& entry : filesystem::directory_iterator(path)) {
        files.push_back(entry.path());
    };

    string word;
    cout << "Enter word/pattern to search: ";
    cin >> word;

    regex pattern;
    try{
        pattern = regex(word);
    } catch (const regex_error& e) {
        cerr << "Invalid regex pattern: " << e.what() << endl;
        return 1;
    }

    vector<thread> threads;

    for (const auto& file : files) {
        threads.push_back(thread(searchInFile, file, ref(pattern)));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}