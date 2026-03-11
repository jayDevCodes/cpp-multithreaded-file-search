#include <iostream>
#include <thread>
#include <vector>
#include "search.h"

using namespace std;

int main() {

    vector<string> files = {
        "file1.txt",
        "file2.txt",
        "file3.txt"
    };

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