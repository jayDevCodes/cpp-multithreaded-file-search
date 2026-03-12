#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <regex>

using namespace std;

void searchInFile(const string& filename, const regex& pattern);

#endif