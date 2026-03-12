#include <iostream>
#include <thread>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <execution>
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

//    vector<string> files = {
//        ("file1.txt"),
//        "file2.txt",
//        "file3.txt"
//    };

    string word;
    cout << "Enter word to search: ";
    cin >> word;

    vector<thread> threads;

    for (const auto& file : files) {
        threads.push_back(thread(searchInFile, file, word));
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}